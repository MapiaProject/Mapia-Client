#include "generated/account/ClientPacketHandler.gen.hpp"
#include "Managers/Manager.h"

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

bool gen::account::PacketHandler::CheckNicknameResPacketHandler(TSharedPtr<Session> session, TSharedPtr<CheckNicknameRes> packet)
{
	return false;
}
