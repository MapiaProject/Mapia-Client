// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActor/NetObject.h"

#include "generated/mmo/Protocol.gen.hpp"
#include "Managers/Network.h"
#include "Managers/Manager.h"

void NetObject::ReceivePacket(const Packet* ReadingPacket)
{
}

bool NetObject::TakeDamage(int Damage)
{
	gen::mmo::AddDamageReq DamagePacket;
	DamagePacket.damageInfo.damage = Damage;
	DamagePacket.damageInfo.objectId = GetId();
	UManager::Net()->Send(ServerType::MMO, &DamagePacket);
	return true;
}

void NetObject::DestroyNetObject()
{
	
}
