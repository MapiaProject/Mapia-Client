// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Session/Session.h"

/**
 * 
 */
class WOS_API FIoThread : FRunnable
{
public:
	FIoThread(TSharedPtr<FSession> Session);
	virtual ~FIoThread() override;
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
private:
	FRunnableThread* Thread;
	TSharedPtr<FSession> Owner;
	FCriticalSection CriticalSection;
};
