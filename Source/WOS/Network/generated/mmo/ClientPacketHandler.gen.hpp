#pragma once
#include "Packet.gen.hpp"
#include "generated/mmo/Enum.gen.hpp"
#include "generated/mmo/Protocol.gen.hpp"
#include "generated/mmo/Struct.gen.hpp"
                         
#ifdef __UNREAL__
#include "winsock2.h"
#include "Network/Packet.h"

using Session = class FSession;

#define STATIC_POINTER_CAST(to, from) StaticCastSharedPtr<to>(from)

#else

template<typename T>
using TSharedPtr = std::shared_ptr<T>;
template<typename T>
using TFunction = std::function<T>;

#define STATIC_POINTER_CAST(to, from) std::static_pointer_cast<to>(from)

class Session;
#endif

#define BIND_HANDLER(pckname, buffer) std::bind(pckname##PacketHandler, std::placeholders::_1, STATIC_POINTER_CAST(pckname, Packet::ParseFrom<pckname>(buffer)));
namespace gen
{
namespace mmo
{
    class PacketHandler
	{
    	using Handler = TFunction<bool(TSharedPtr<Session>)>;
	public:
		static Handler getHandler(std::span<char> buffer)
        {
            PacketId id = PacketId::NONE;
			std::memcpy(&id, buffer.data(), sizeof(unsigned short));
			id = (PacketId)ntohs((u_short)id);
            
            switch (id)
            {
            case PacketId::NONE:
                break;
			case ENTER_GAME_RES:
				return BIND_HANDLER(EnterGameRes, buffer);
			case SPAWN:
				return BIND_HANDLER(Spawn, buffer);
			case NOTIFY_MOVE:
				return BIND_HANDLER(NotifyMove, buffer);
			case NOTIFY_CHAT:
				return BIND_HANDLER(NotifyChat, buffer);
            default:
                break;
            }
            return nullptr;
        }
        static bool handlePacket(TSharedPtr<Session> session, std::span<char> buffer)
        {
            auto handler = getHandler(buffer);
            if (!handler || !session)
                return false;
            return handler(session);
        }
		static bool EnterGameResPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameRes> packet);
		static bool SpawnPacketHandler(TSharedPtr<Session> session, TSharedPtr<Spawn> packet);
		static bool NotifyMovePacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyMove> packet);
		static bool NotifyChatPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyChat> packet);
	};
}
}
