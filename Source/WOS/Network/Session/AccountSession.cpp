#include "AccountSession.h"

#include "generated/account/ClientPacketHandler.gen.hpp"

void FAccountSession::OnConnected()
{
	FSession::OnConnected();
}

void FAccountSession::OnDisconnected()
{
	FSession::OnDisconnected();
}

void FAccountSession::OnReceive(std::span<char> buffer, int32 length)
{
	RECV_PACKET(account)
}