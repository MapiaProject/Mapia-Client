#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/NetObjectManager.h"
#include "Managers/Manager.h"

using namespace gen;

bool mmo::PacketHandler::EnterGameResPacketHandler(Session* session, TSharedPtr<EnterGameRes> packet)
{
	UManager::Get()->HandleEnterGame(packet.Get());
	return false;
}

bool mmo::PacketHandler::EnterMapResPacketHandler(Session* session, TSharedPtr<EnterMapRes> packet)
{
	UManager::Get()->HandleEnterMap(packet.Get());
	return false;
}

bool mmo::PacketHandler::SpawnPacketHandler(Session* session, TSharedPtr<Spawn> packet)
{
	UManager::Object()->HandleSpawnPlayer(packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::NotifyLeaveMapPacketHandler(Session* session, TSharedPtr<NotifyLeaveMap> packet)
{
	UManager::Object()->HandleLeaveMap(packet.Get());
	return false;
}

bool mmo::PacketHandler::NotifyMovePacketHandler(Session* session, TSharedPtr<NotifyMove> packet)
{
	UManager::Object()->HandleNetObjectPacket(packet.Get()->objectId, packet.Get());
	return false;
}

bool mmo::PacketHandler::NotifyChatPacketHandler(Session* session, TSharedPtr<NotifyChat> packet)
{
	UManager::Get()->HandleChat(packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::NotifyDamagedPacketHandler(Session* session, TSharedPtr<NotifyDamaged> packet)
{
	UManager::Object()->HandleNetObjectPacket(packet.Get()->damageResult.objectId, packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::NotifySpawnPacketHandler(Session* session, TSharedPtr<NotifySpawn> packet)
{
	UManager::Object()->HandleNotifySpawn(packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::TakeAttackPacketHandler(Session* session, TSharedPtr<TakeAttack> packet)
{
	UManager::Object()->HandleNetObjectPacket(packet.Get()->target, packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::ObtainItemPacketHandler(Session* session, TSharedPtr<ObtainItem> packet)
{
	return false;
}
