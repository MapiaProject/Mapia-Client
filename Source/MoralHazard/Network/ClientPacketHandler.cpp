#include "Session.h"
#include "generated/ClientPacketHandler.gen.hpp"

using namespace gen;

bool gen::PacketHandler::LoginResPacketHandler(TSharedPtr<Session> session, TSharedPtr<LoginRes> packet)
{
	return false;
}

bool gen::PacketHandler::NotifyRoomListPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyRoomList> packet)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, TEXT("Room len : ") + FString::FromInt(packet->roomList.size()));
	for(const auto& room : packet->roomList)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, TEXT("name : ") + room.name);
	}
	return true;
}

bool gen::PacketHandler::EnterRoomResPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterRoomRes> packet)
{
	return false;
}
