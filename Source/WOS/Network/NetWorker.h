// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class WOS_API FNetWorker final : public FRunnable
{
public:
	FNetWorker(class FSession* SessionRef);
	virtual ~FNetWorker() override;
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;
private:
	char m_buffer[4096];
	FRunnableThread* Thread = nullptr;
	FSession* Session;
};
