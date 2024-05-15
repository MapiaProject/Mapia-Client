#include "Rpc.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"

TMap<uint16, std::pair<void*, std::function<void(std::span<char>)>>> RpcView::RpcFuncTable;
uint16 RpcView::RpcId = 0;

void RpcView::SendRpc(Packet* RpcPacket)
{
	UManager::Net()->Send(ServerType::MMO, RpcPacket);
}
