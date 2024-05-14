#include "Rpc.h"

TMap<FString, RpcSystem::RpcProc> RpcSystem::RpcFuncTable;

void RpcSystem::Register(FStringView FuncName, RpcProc ProcFunc)
{
	RpcFuncTable[FuncName.GetData()] = ProcFunc;
}

void RpcSystem::Execute(Rpc<> Rpc)
{
	FString FuncName;
	Rpc >> FuncName;

	RpcFuncTable[FuncName](Rpc);
}
