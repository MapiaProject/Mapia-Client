#include "generated/account/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"

using namespace gen;

bool account::PacketHandler::LoginResPacketHandler(Session* Session, TSharedPtr<LoginRes> packet)
{
	UManager::Get()->HandleLogin(packet.Get());
	return false;
}

bool account::PacketHandler::RegisterResPacketHandler(Session* Session, TSharedPtr<RegisterRes> packet)
{
	UManager::Get()->HandleRegister(packet.Get());
	return false;
}

bool account::PacketHandler::CheckNicknameResPacketHandler(Session* Session, TSharedPtr<CheckNicknameRes> packet)
{
	UManager::Get()->HandleCheckNickname(packet.Get());
	return false;
}
