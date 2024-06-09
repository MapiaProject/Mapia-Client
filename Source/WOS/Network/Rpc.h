#pragma once

#include "CoreMinimal.h"

#include "Packet.h"
#include "GameActor/NetObject.h"
#include "Managers/Manager.h"
#include "Managers/NetObjectManager.h"
#include "Util/Templates.h"

#define THIS_CLASS std::remove_pointer<decltype(this)>::type

#define RPC(Func) _RPC##Func()
#define RPC_FUNCTION(Func) inline uint16 RPC(Func) { static uint16 RpcId = RpcView::Register(&THIS_CLASS::Func); return RpcId; }
#define CallRPC(Func, Target, ...) Execute(&THIS_CLASS::Func, this, RPC(Func), Target, __VA_ARGS__);

enum class RpcTarget : uint8
{
	All,
	Other
};

template<class T, class... Args> requires std::is_base_of_v<NetObject, T>
class Rpc : public Packet
{
public:
	Rpc(void(T::*RpcFunc)(Args...), uint16 Id) : Packet(Id, RPC), RpcFunc(RpcFunc)
	{
	}
public:
	void Execute(std::span<char> Buffer)
	{
		SetBuffer(Buffer);
		Packet::Read();
		
		std::tuple<Args...> Params;
		std::apply(bind(&Rpc::ReadParameter, this), Params);
		std::apply(bind(RpcFunc, static_cast<T*>(UManager::Object()->GetObjectById(Caller))), Params);
	}
	void WriteParameter(Args... ArgsList)
	{
		*this << static_cast<uint8>(Target) << Caller;
		((*this << ArgsList), ...);
	}
	void ReadParameter(Args&... ArgsList)
	{
		*this >> reinterpret_cast<uint8&>(Target) >> Caller;
		((*this >> ArgsList), ...);
		Reset();
	}
public:
	FORCEINLINE void SetTarget(RpcTarget NotifyTarget) { this->Target = NotifyTarget; }
	FORCEINLINE void SetCaller(uint64 Id) { this->Caller = Id; }
	FORCEINLINE void SetBuffer(std::span<char> Buffer) { Data() = std::vector(Buffer.begin(), Buffer.end()); }
private:
	uint64 Caller;
	RpcTarget Target;
	void(T::*RpcFunc)(Args...);
};

class RpcView
{
	struct RpcInterface
	{
		void* Owner;
		std::function<void(std::span<char>)> Execute;
	};
public:
	template<class T, class... Args>
	static uint16 Register(void(T::*RpcFunc)(Args...))
	{
		auto RpcObject = new Rpc<T, Args...>(RpcFunc, ++RpcId);
		RpcInterface Interface
		{
			.Owner = RpcObject,
			.Execute = std::bind(&Rpc<T, Args...>::Execute, RpcObject, std::placeholders::_1)
		};
		
		RpcFuncTable.Add(RpcId, Interface);
		return RpcId;
	}
	
	template<class T, class... Args>
	static void Execute(void(T::*)(Args...), T* Owner, uint16 Id, RpcTarget Target, Args... ArgsList)
	{
		auto RpcObj = static_cast<Rpc<T, Args...>*>(RpcFuncTable[Id].Owner);
		RpcObj->SetTarget(Target);
		RpcObj->SetCaller(Owner->GetId());
		RpcObj->WriteParameter(Forward<Args>(ArgsList)...);
		SendRpc(RpcObj);
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