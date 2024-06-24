#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/NetObjectManager.h"
#include "Managers/Manager.h"

using namespace gen;

bool mmo::PacketHandler::EnterGameResPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameRes> packet)
{
	UManager::Get()->HandleEnterGame(packet.Get());
	return false;
}

bool mmo::PacketHandler::EnterMapResPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterMapRes> packet)
{
	UManager::Get()->HandleEnterMap(packet.Get());
	return false;
}

bool mmo::PacketHandler::SpawnPacketHandler(TSharedPtr<Session> session, TSharedPtr<Spawn> packet)
{
	UManager::Object()->HandleSpawnPlayer(packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::NotifyLeaveMapPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyLeaveMap> packet)
{
	UManager::Object()->HandleLeaveMap(packet.Get());
	return false;
}

bool mmo::PacketHandler::NotifyMovePacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyMove> packet)
{
	UManager::Object()->HandleNetObjectPacket(packet.Get()->objectId, packet.Get());
	return false;
}

bool mmo::PacketHandler::NotifyChatPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyChat> packet)
{
	UManager::Get()->HandleChat(packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::SpawnMonsterPacketHandler(TSharedPtr<Session> session, TSharedPtr<SpawnMonster> packet)
{
	//UManager::Get()->HandleSpawnMonster(packet.Get());
	UManager::Object()->HandleSpawnMonster(packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::NotifyDamagedPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyDamaged> packet)
{
	UManager::Object()->HandleNetObjectPacket(packet.Get()->damageResult.objectId, packet.Get());
	return false;
}

bool gen::mmo::PacketHandler::TakeAttackPacketHandler(TSharedPtr<Session> session, TSharedPtr<TakeAttack> packet)
{
	UManager::Object()->HandleNetObjectPacket(packet.Get()->target, packet.Get());
	return false;
}
