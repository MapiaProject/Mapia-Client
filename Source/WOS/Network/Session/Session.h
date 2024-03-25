#pragma once
#include "net/Socket.hpp"

class FSession : public TSharedFromThis<FSession>, public FRunnable
{
	friend class FIoThread;
public:
	FSession(net::Socket* socket);
	virtual ~FSession() override;
public:
	virtual void OnConnected();
	virtual void OnDisconnected();
	virtual void OnReceive(std::span<char> buffer, int32 length);
public:
	void Send(std::span<char> data);
	void Send(class Packet* pkt);
public:
	net::Socket* GetHandle() const;
	void Flush();
protected:
	void PushJob(TFunction<void()> Functor);
	
	template<class TRet, class ...TArgs>
	FORCEINLINE void PushJob(TFunction<TRet(TArgs...)> Functor, TArgs... Args)
	{
		JobQue.Enqueue([=] { Functor(Args...); });
	}

public:
	virtual uint32 Run() override;

private:
	FRunnableThread* Thread;
	net::Socket* Socket;
	char m_buffer[4096];
	TQueue<TFunction<void()>> JobQue;
};