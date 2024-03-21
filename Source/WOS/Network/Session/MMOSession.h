#pragma once
#include "CoreMinimal.h"
#include "Session.h"

class FMMOSession final : public FSession
{
public:
	explicit FMMOSession(net::Socket* socket)
		: FSession(socket)
	{
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnReceive(std::span<char> buffer, int32 length) override;
};