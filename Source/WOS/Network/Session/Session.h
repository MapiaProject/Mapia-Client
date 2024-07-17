#pragma once
#include "net/Socket.hpp"
#include "Rpc.h"

#define RECV_PACKET(name) \
FSession::OnReceive(buffer, length); \
\
uint16 Id = 0;\
memcpy(&Id, buffer.data(), 2);\
if ((Id >> 15) & 1)\
{\
	RpcView::RecvRPC(buffer, Id);\
}\
else\
{\
	const auto Handler = gen::name::PacketHandler::GetHandler(Id, buffer);\
	const TSharedPtr<FSession> SharedThis = AsShared();\
	\
	PushJob(Handler, SharedThis);\
}\

class FSession : public TSharedFromThis<FSession>
{
	friend class FIoThread;
public:
	FSession(TSharedPtr<net::Socket> Socket, ServerType Type);
	virtual ~FSession();
public:
	virtual void OnConnected();
	virtual void OnDisconnected();
	virtual void OnReceive(std::span<char> buffer, int32 length);
public:
	void Send(std::span<char> data);
	void Send(class Packet* pkt);
public:
 	TSharedPtr<net::Socket> GetHandle();
	void Flush();
	void Disconnect() const;
	ServerType GetType() const;

protected:
	void PushJob(TFunction<void()> Functor);
	
	template<class TRet, class ...TArgs>
	FORCEINLINE void PushJob(TFunction<TRet(TArgs...)> Functor, TArgs... Args)
	{
		JobQue.Enqueue([=] { Functor(Args...); });
	}
private:
	ServerType Type;
	TSharedPtr<class FNetWorker> Worker;
	TSharedPtr<net::Socket> Socket;
	TQueue<TFunction<void()>> JobQue;
};