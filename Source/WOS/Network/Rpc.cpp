#include "Rpc.h"
#include "Managers/Manager.h"
#include "Managers/Network.h"

TMap<uint16, RpcView::RpcInterface> RpcView::RpcFuncTable;
uint16 RpcView::RpcId = 0;

void RpcView::SendRpc(Packet* RpcPacket)
{
	UManager::Net()->Send(ServerType::MMO, RpcPacket);
	RpcPacket->Reset();
}
