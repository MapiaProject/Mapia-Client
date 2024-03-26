// Fill out your copyright notice in the Description page of Project Settings.


#include "NetWorker.h"

#include "Session/Session.h"

FNetWorker::FNetWorker(TSharedPtr<FSession> SessionRef) : m_buffer{ 0, }, Session(SessionRef)
{
	Thread = FRunnableThread::Create(this, TEXT("Network Worker"));
}

FNetWorker::~FNetWorker()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}

bool FNetWorker::Init()
{
	return true;
}

uint32 FNetWorker::Run()
{
	const auto SessionPtr = Session.Pin();
	while (SessionPtr->GetHandle()->isOpen())
	{
		const auto Length = SessionPtr->GetHandle()->receive(m_buffer);
		if (Length > 0)
			SessionPtr->OnReceive(m_buffer, Length);
		else
		{
			SessionPtr->OnDisconnected();
			break;
		}
	}
	return 0;
}

void FNetWorker::Exit()
{
}

void FNetWorker::Stop()
{
}
