#pragma once

#include "CoreMinimal.h"

#include "Packet.h"
#include "GameActor/NetObject.h"

#define RPC_FUNCTION(Class, Func) TUniquePtr<RpcObject> _RPC##Func() { return RpcView::Register(this, &Class::Func); }
#define BIND_RPC(Class, Func) _RPC##Func();

enum class RpcTarget : uint16
{
	All,
	Other
};

template<class T, class... Args> requires std::is_base_of_v<NetObject, T>
class Rpc : public Packet
{
public:
	Rpc(T* OwnerPtr, void(T::*RpcMethod)(Args...), uint16 Id) : Packet(Id, RPC), Owner(OwnerPtr)
	{
		RpcFunc = std::bind(RpcMethod, Owner);
	}
public:
	void Read(std::span<char> Buffer)
	{
		SetBuffer(Buffer);
		Packet::Read();

		*this >> reinterpret_cast<uint16&>(Target);
		std::apply([this](Args&... ArgsList)
		{
			((*this  >> ArgsList), ...);
		}, Params);
		std::apply(RpcFunc, Params);
	}
	void Write(Args... ArgsList)
	{
		*this << static_cast<uint16>(Target);
		((*this << ArgsList), ...);
	}
public:
	void SetTarget(RpcTarget NotifyTarget) { this->Target = NotifyTarget; }
	void SetBuffer(std::span<char> Buffer) { Data() = std::vector(Buffer.begin(), Buffer.end()); };
private:
	RpcTarget Target;
	T* Owner;
	std::tuple<Args...> Params;
	std::function<void(Args...)> RpcFunc;
};

class RpcObject;

class RpcView
{
public:
	template<class T, class... Args>
	static TUniquePtr<RpcObject> Register(T* Owner, void(T::*RpcFunc)(Args...))
	{
		auto RpcObj = new Rpc<T, Args...>(Owner, RpcFunc, ++RpcId);
		auto ReadFunc = std::bind(&Rpc<T, Args...>::Read, RpcObj, std::placeholders::_1);
		RpcFuncTable.Emplace(RpcId, { static_cast<void*>(RpcObj), ReadFunc });

		return MakeUnique<RpcObject>(RpcId);
	}

	template<class T, class... Args>
	static void Execute(uint16 RpcFuncId, RpcTarget Target, Args&&... ArgsList)
	{
		auto RpcObj = static_cast<Rpc<T, Args...>*>(RpcFuncTable[RpcFuncId].first);
		RpcObj->SetTarget(Target);
		RpcObj->Write(Forward<Args>(ArgsList)...);
		SendRpc(RpcObj);
	}

	static void RecvRPC(std::span<char> buffer, uint16 Id)
	{
		auto Read = RpcFuncTable[0x7FFF & Id].second;
		Read(buffer);
	}
private:
	static void SendRpc(Packet* RpcPacket);
private:
	static TMap<uint16, std::pair<void*, std::function<void(std::span<char>)>>> RpcFuncTable;
	static uint16 RpcId;
};

class RpcObject
{
public:
	RpcObject(uint16 Id) : RpcId(Id) {}

	template<class T, class... Args>
	void Call(RpcTarget Target, Args&&... ArgsList)
	{
		RpcView::Execute<T>(RpcId, Target, ArgsList...);
	}
private:
	uint16 RpcId;
};