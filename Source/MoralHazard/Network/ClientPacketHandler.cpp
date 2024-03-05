#include "Session.h"
#include "generated/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"

using namespace gen;

bool gen::PacketHandler::LoginResPacketHandler(TSharedPtr<Session> session, TSharedPtr<LoginRes> packet)
{
	return false;
}

bool gen::PacketHandler::NotifyRoomListPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyRoomList> packet)
{
	UManager::Instance()->RefreshRoom(*packet);
	return true;
}

bool gen::PacketHandler::RoomEventResPacketHandler(TSharedPtr<Session> session, TSharedPtr<RoomEventRes> packet)
{
	UManager::Instance()->HandleRoomEventResult(*packet);
	return false;
}
