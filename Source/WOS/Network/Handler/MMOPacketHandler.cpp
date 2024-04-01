#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"

using namespace gen;

bool mmo::PacketHandler::EnterGameResPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameRes> packet)
{
	UManager::Get()->HandleEnterGame(packet.Get());
	return false;
}

bool mmo::PacketHandler::SpawnPacketHandler(TSharedPtr<Session> session, TSharedPtr<Spawn> packet)
{
	UManager::Get()->HandleSpawn(packet.Get());
	return false;
}
