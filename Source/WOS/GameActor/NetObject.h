// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Packet.h"

/**
 * 
 */
class WOS_API NetObject
{
public:
	virtual void RecievePacket(const Packet* ReadingPacket) = 0;
	virtual void TakeDamage(int Damage);
	int GetNetObjectId();

private:
	int NetObjectId;

	friend class UNetObjectManager;
};
