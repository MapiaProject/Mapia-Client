#include "WOSGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "generated/account/ClientPacketHandler.gen.hpp"
#include "Kismet/GameplayStatics.h"
#include "Managers/Manager.h"
#include "UI/LoginPopup.h"

using namespace gen;

bool account::PacketHandler::LoginResPacketHandler(TSharedPtr<Session> session, TSharedPtr<LoginRes> packet)
{
	UManager::Get()->HandleLogin(packet.Get());
	return false;
}

bool account::PacketHandler::RegisterResPacketHandler(TSharedPtr<Session> session, TSharedPtr<RegisterRes> packet)
{
	UManager::Get()->HandleRegister(packet.Get());
	return false;
}