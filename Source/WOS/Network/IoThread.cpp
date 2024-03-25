// Fill out your copyright notice in the Description page of Project Settings.


#include "IoThread.h"

#include "Managers/Network.h"

FIoThread::FIoThread(TSharedPtr<FSession> Session)
{
	Owner = Session;
	Thread = FRunnableThread::Create(this, TEXT("Net I/O Thread"));
}

FIoThread::~FIoThread()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}

bool FIoThread::Init()
{
	return FRunnable::Init();
}

uint32 FIoThread::Run()
{
	while (Owner->GetHandle()->isOpen())
	{
		const auto Length = Owner->GetHandle()->receive(Owner->m_buffer);
		if (Length > 0)
			Owner->OnReceive(Owner->m_buffer, Length);
		else
		{
			Owner->OnDisconnected();
			break;
		}
	}
	return 0;
}

void FIoThread::Stop()
{
	FRunnable::Stop();
}

void FIoThread::Exit()
{
	FRunnable::Exit();
}