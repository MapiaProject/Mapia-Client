#include "Session.h"

#include "Packet.h"

FSession::FSession(net::Socket* socket) : Socket(socket)
{
	ZeroMemory(&m_buffer, sizeof(m_buffer));
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
	while (!HandlerQue.IsEmpty())
	{
		TFunction<bool(TSharedPtr<FSession>)> Handler;
		if (HandlerQue.Dequeue(Handler))
		{
			if (Handler)
				bool Result = Handler(AsShared());
		}
	}
}