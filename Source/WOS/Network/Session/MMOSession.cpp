#include "MMOSession.h"

#include "Rpc.h"
#include "generated/mmo/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"
#include "Managers/Network.h"
#include "Managers/UISystem.h"
#include "UI/LoginUI.h"

void FMMOSession::OnConnected()
{
	FSession::OnConnected();

	gen::mmo::EnterGameReq Req;
	Req.name = Cast<ULoginUI>(UManager::UI()->LoginWidgetObject)->GetID().ToString();
	Send(&Req);
	UManager::Get()->IsConnected = true;
}

void FMMOSession::OnDisconnected()
{
	FSession::OnDisconnected();
	auto g = GEngine;
	auto v = g->GameViewport;
	if (v != nullptr) {
		auto w = v->GetWorld();
		auto o = UManager::Get(w);
		o->IsConnected = false;
	}
}

void FMMOSession::OnReceive(std::span<char> buffer, int32 length)
{
	RECV_PACKET(mmo);
}
