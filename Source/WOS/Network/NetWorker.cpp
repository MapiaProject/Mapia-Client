// Fill out your copyright notice in the Description page of Project Settings.


#include "NetWorker.h"

#include "Managers/Network.h"
#include "Session/Session.h"

FNetWorker::FNetWorker(FSession* SessionRef) : m_buffer{ 0, }, Session(SessionRef)
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
	while (Session && Session->GetHandle()->isOpen())
	{
		const auto Length = Session->GetHandle()->receive(m_buffer);
		if (Length > 0)
			Session->OnReceive(m_buffer, Length);
		else
		{
			Session->OnDisconnected();
			UManager::Net()->RemoveSession(Session->GetType());
			delete Session;
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
