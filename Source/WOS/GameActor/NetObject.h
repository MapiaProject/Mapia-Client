// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/Packet.h"

inline Packet& operator<<(Packet& Pkt, FRotator Rotator)
{
	Pkt << Rotator.Pitch << Rotator.Yaw << Rotator.Roll;
	return Pkt;
}
inline Packet& operator>>(Packet& Pkt, FRotator Rotator)
{
	Pkt >> Rotator.Pitch >> Rotator.Yaw >> Rotator.Roll;
	return Pkt;
}

/**
 * 
 */
class WOS_API NetObject
{
	friend class UNetObjectManager;
public:
	virtual void RecievePacket(const Packet* ReadingPacket) = 0;
	virtual void TakeDamage(int Damage);
	FORCEINLINE uint64 GetId() const { return ObjectId; };
private:
	uint64 ObjectId;
};
