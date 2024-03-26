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
	FSession::OnReceive(buffer, length);
	
	const auto Handler = gen::account::PacketHandler::getHandler(buffer);
	const TSharedPtr<FSession> SharedThis = AsShared();
	
	PushJob(Handler, SharedThis);
}