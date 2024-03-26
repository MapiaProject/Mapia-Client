#pragma once
#include "net/Socket.hpp"

class FSession : public TSharedFromThis<FSession>
{
	friend class FIoThread;
public:
	FSession(TSharedPtr<net::Socket> socket);
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

protected:
	void PushJob(TFunction<void()> Functor);
	
	template<class TRet, class ...TArgs>
	FORCEINLINE void PushJob(TFunction<TRet(TArgs...)> Functor, TArgs... Args)
	{
		JobQue.Enqueue([=] { Functor(Args...); });
	}
private:
	TSharedPtr<class FNetWorker> Worker;
	TSharedPtr<net::Socket> Socket;
	TQueue<TFunction<void()>> JobQue;
};