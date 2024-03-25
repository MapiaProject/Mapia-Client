#include "Session.h"
#include "Packet.h"

FSession::FSession(net::Socket* socket) : Socket(socket)
{
	ZeroMemory(&m_buffer, sizeof(m_buffer));
}

FSession::~FSession()
{
}

void FSession::OnConnected()
{
}

void FSession::OnDisconnected()
{
}

void FSession::OnReceive(std::span<char> buffer, int32 length)
{
	if (length <= 2)
		return;
}

void FSession::Send(std::span<char> data)
{
	if (!Socket->send(data))
		OnDisconnected();
}

void FSession::Send(Packet* pkt)
{
	pkt->Write();
	Send(pkt->Data());
}

net::Socket* FSession::GetHandle() const
{
	return this->Socket;
}

void FSession::Flush()
{
	while (!JobQue.IsEmpty())
	{
		TFunction<void()> Handler;
		if (JobQue.Dequeue(Handler))
		{
			if (Handler) Handler();
		}
	}
}

void FSession::PushJob(TFunction<void()> Functor)
{
	JobQue.Enqueue(Functor);
}
