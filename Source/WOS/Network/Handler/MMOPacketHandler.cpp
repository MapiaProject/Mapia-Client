#include "generated/mmo/ClientPacketHandler.gen.hpp"
	
using namespace gen;

bool mmo::PacketHandler::NotifyRoomListPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyRoomList> packet)
{
	return false;
}

bool mmo::PacketHandler::RoomEventResPacketHandler(TSharedPtr<Session> session, TSharedPtr<RoomEventRes> packet)
{
	
	return false;
}
bool mmo::PacketHandler::NotifyPlayerListPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyPlayerList> packet)
{
	
	return false;
}