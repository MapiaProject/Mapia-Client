#pragma once

#include "CoreMinimal.h"

#include "Packet.h"
#include "GameActor/NetObject.h"

#define RPC(Func) _RPC##Func()
#define RPC_FUNCTION(Class, Func) uint16 RPC(Func) { static uint16 RpcId = RpcView::Register(&Class::Func); return RpcId; }

enum class RpcTarget : uint16
{
	All,
	Other
};

template<class T, class... Args> requires std::is_base_of_v<NetObject, T>
class Rpc : Packet
{
public:
	Rpc(void(T::*RpcFunc)(Args...), uint16 Id) : Packet(Id, RPC), Id(Id), RpcFunc(RpcFunc)
	{
	}
public:
	void Execute(std::span<char> Buffer)
	{
		SetBuffer(Buffer);
		Packet::Read();

		*this >> reinterpret_cast<uint16&>(Target);
		std::tuple<Args...> Params;
		std::apply([this](Args&... ArgsList)
		{
			((*this >> ArgsList), ...);
		}, Params);

		for (const auto& Object : Objects)
			std::apply(std::bind(RpcFunc, Object), Params);
	}
	void WriteParameter(Args... ArgsList)
	{
		*this << static_cast<uint16>(Target);
		((*this << ArgsList), ...);
	}
public:
	void SetTarget(RpcTarget NotifyTarget) { this->Target = NotifyTarget; }
	void SetBuffer(std::span<char> Buffer) { Data() = std::vector(Buffer.begin(), Buffer.end()); }
	void Add(void* Ptr) { Objects.Add(static_cast<T*>(Ptr)); }
private:
	uint16 Id;
	RpcTarget Target;
	void(T::*RpcFunc)(Args...);
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
	static uint16 Register(void(T::*RpcFunc)(Args...))
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
	static void Execute(uint16 Id, RpcTarget Target, Args&&... ArgsList)
	{
		auto RpcObj = static_cast<Rpc<T, Args...>*>(RpcFuncTable[Id].Owner);
		RpcObj->SetTarget(Target);
		RpcObj->WriteParameter(Forward<Args>(ArgsList)...);
		SendRpc(reinterpret_cast<Packet*>(RpcObj));
	}
	
	static void Add(uint16 Id, void* Owner)
	{
		RpcFuncTable[Id].Add(Owner);
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