#pragma once

#include "CoreMinimal.h"

#include "Packet.h"
#include "GameActor/NetObject.h"
#include "Util/Templates.h"

#define THIS_CLASS std::remove_pointer<decltype(this)>::type

#define RPC(Func) _RPC##Func()
#define RPC_FUNCTION(Func) inline uint16 RPC(Func) { static uint16 RpcId = RpcView::Register(&THIS_CLASS::Func); return RpcId; }
#define CallRPC(Func, Target, ...) Execute(&THIS_CLASS::Func, this, RPC(Func), Target, __VA_ARGS__);

enum class RpcTarget : uint16
{
	All,
	Other
};

template<class T, class... Args> requires std::is_base_of_v<NetObject, T>
class Rpc : Packet
{
public:
	Rpc(void(T::*RpcFunc)(bool, Args...), uint16 Id) : Packet(Id, RPC), RpcFunc(RpcFunc)
	{
	}
public:
	void Execute(std::span<char> Buffer)
	{
		SetBuffer(Buffer);
		Packet::Read();

		uint64 Caller;
		*this >> reinterpret_cast<uint16&>(Target) >> Caller;

		std::tuple<Args...> Params;
		std::apply(bind(&Rpc::ReadParameter, this), Params);
		for (const auto& Object : Objects)
		{
			if (Object != nullptr)
				std::apply(bind(RpcFunc, Object, CallerId == Caller), Params);
			else Objects.Remove(Object);
		}
	}
	void WriteParameter(Args... ArgsList)
	{
		*this << static_cast<uint16>(Target) << CallerId;
		((*this << ArgsList), ...);
	}
	void ReadParameter(Args&... ArgsList)
	{
		((*this >> ArgsList), ...);
	}
public:
	void SetTarget(RpcTarget NotifyTarget) { this->Target = NotifyTarget; }
	void SetBuffer(std::span<char> Buffer) { Data() = std::vector(Buffer.begin(), Buffer.end()); }
	void Add(void* Ptr) { Objects.AddUnique(static_cast<T*>(Ptr)); }
	void SetCaller(uint16 Id) { CallerId = Id; }
private:
	uint64 CallerId;
	RpcTarget Target;
	void(T::*RpcFunc)(bool, Args...);
	TArray<T*> Objects;
};

class RpcView
{
	struct RpcInterface
	{
		void* Owner;
		std::function<void(void*)> Add;
		std::function<void(std::span<char>)> Execute;
	};
public:
	template<class T, class... Args>
	static uint16 Register(void(T::*RpcFunc)(bool, Args...))
	{
		auto RpcObject = new Rpc<T, Args...>(RpcFunc, ++RpcId);
		RpcInterface Interface
		{
			.Owner = RpcObject,
			.Add = std::bind(&Rpc<T, Args...>::Add, RpcObject, std::placeholders::_1),
			.Execute = std::bind(&Rpc<T, Args...>::Execute, RpcObject, std::placeholders::_1)
		};
		
		RpcFuncTable.Add(RpcId, Interface);
		return RpcId;
	}
	
	template<class T, class... Args>
	static void Execute(void(T::*)(bool, Args...), T* Owner, uint16 Id, RpcTarget Target, Args... ArgsList)
	{
		auto RpcObj = static_cast<Rpc<T, Args...>*>(RpcFuncTable[Id].Owner);
		RpcObj->SetTarget(Target);
		RpcObj->SetCaller(Owner->GetId());
		RpcObj->WriteParameter(Forward<Args>(ArgsList)...);
		RpcObj->Add(Owner);
		SendRpc(reinterpret_cast<Packet*>(RpcObj));
	}

	static void RecvRPC(std::span<char> buffer,  uint16 Id)
	{
		RpcFuncTable[0x7FFF & Id].Execute(buffer);
	}
private:
	static void SendRpc(Packet* RpcPacket);
private:
	static TMap<uint16, RpcInterface> RpcFuncTable;
	static uint16 RpcId;
};