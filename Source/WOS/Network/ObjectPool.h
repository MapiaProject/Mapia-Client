#pragma once

template<class T>
class ObjectPool
{
public:
	static T* Pop()
	{
		if (!m_pool.IsEmpty())
		{
			T* ptr = *m_pool.Peek();
			m_pool.Pop();
			return ptr;
		}
		return static_cast<T*>(FMemory::Malloc(sizeof(T)));
	}
	static std::vector<T*> Pop(size_t count)
	{
		std::vector<T*> objects;
		for (int i = 0; i < count; ++i)
			objects.push_back(Pop());
		return objects;
	}
	static void Push(T* ptr)
	{
		if (ptr)
		{
			m_pool.Enqueue(ptr);
		}
	}
	static void Push(T* ptr, size_t count)
	{
		T* p = ptr;
		for (int i = 0; i < count; ++i)
		{
			Push(p);
			p += sizeof(T);
		}
	}
private:
	static TQueue<T*> m_pool;
};

template<class T>
TQueue<T*> ObjectPool<T>::m_pool;

#define USE_POOL(className)\
public:\
FORCEINLINE void* operator new(size_t)\
{\
	return reinterpret_cast<void*>(ObjectPool<className>::Pop());\
}\
FORCEINLINE void* operator new[](size_t count)\
{\
	return reinterpret_cast<void*>(ObjectPool<className>::Pop(count/sizeof(className)).data());\
}\
FORCEINLINE void operator delete(void* ptr)\
{\
	ObjectPool<className>::Push(reinterpret_cast<className*>(ptr));\
}\
FORCEINLINE void operator delete[](void* ptr, size_t count)\
{\
	ObjectPool<className>::Push(reinterpret_cast<className*>(ptr), count/sizeof(className));\
}\
private:\
