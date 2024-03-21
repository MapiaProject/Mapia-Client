#include "MMOSession.h"

#include "generated/mmo/ClientPacketHandler.gen.hpp"

void FMMOSession::OnConnected()
{
	FSession::OnConnected();
}

void FMMOSession::OnDisconnected()
{
	FSession::OnDisconnected();
}

void FMMOSession::OnReceive(std::span<char> buffer, int32 length)
{
	FSession::OnReceive(buffer, length);
	const auto Handler = gen::mmo::PacketHandler::getHandler(buffer);
	HandlerQue.Enqueue(Handler);
}
