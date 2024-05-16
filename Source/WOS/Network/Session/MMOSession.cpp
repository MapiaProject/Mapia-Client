#include "MMOSession.h"

#include "Rpc.h"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"

void FMMOSession::OnConnected()
{
	FSession::OnConnected();

	gen::mmo::EnterGameReq Req;
	Req.name = UManager::Net()->GetUUID().value();
	Send(&Req);
}

void FMMOSession::OnDisconnected()
{
	FSession::OnDisconnected();
}

void FMMOSession::OnReceive(std::span<char> buffer, int32 length)
{
	RECV_PACKET(mmo);
}
