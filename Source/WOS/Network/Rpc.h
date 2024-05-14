#pragma once
#include "Packet.h"

#define RPC(className, FuncName, ...)


template<typename... Args>
class Rpc : public Packet
{
public:
	Rpc(Args&&... RpcParam)
	{
		std::string head = "RPC";
		Data().resize(3);
		std::copy(head.begin(), head.end()-1, Data().begin());

		((*this << std::forward<Args>(RpcParam)), ...);
	}
	virtual void Read() override
	{
	}
};


class RpcSystem
{
	using RpcProc = TFunction<void(Rpc<>)>;
public:
	static void Register(FStringView FuncName, RpcProc ProcFunc);
	static void Execute(Rpc<> Rpc);
private:
	static TMap<FString, RpcProc> RpcFuncTable;
};