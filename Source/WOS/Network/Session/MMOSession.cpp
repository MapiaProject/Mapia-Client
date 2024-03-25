#include "MMOSession.h"

#include "generated/account/ClientPacketHandler.gen.hpp"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"

void FMMOSession::OnConnected()
{
	FSession::OnConnected();
}

void FMMOSession::OnDisconnected()
{
	FSession::OnDisconnected();
	PushJob([]
	{
		auto UUID = UManager::Net()->GetUUID();
		if (UUID.has_value())
		{
			gen::account::LogoutReq Req;
			Req.uuid = UUID.value();
			UManager::Net()->Send(ServerType::Account, &Req);
		}
	});
}

void FMMOSession::OnReceive(std::span<char> buffer, int32 length)
{
	FSession::OnReceive(buffer, length);
	
	const auto Handler = gen::mmo::PacketHandler::getHandler(buffer);
	const TSharedPtr<FSession> SharedThis = AsShared();
	
	PushJob(Handler, SharedThis);
}
