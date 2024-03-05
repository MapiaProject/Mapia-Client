#pragma once
#include "Packet.gen.hpp"
#include "generated/Enum.gen.hpp"
#include "generated/Protocol.gen.hpp"
#include "generated/Struct.gen.hpp"
                         
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
    class PacketHandler
	{
    	using Handler = TFunction<bool(TSharedPtr<Session>)>;
	public:
		static Handler getHandler(std::span<char> buffer)
        {
            gen::PacketId id = gen::PacketId::NONE;
			std::memcpy(&id, buffer.data(), sizeof(unsigned short));
			id = (gen::PacketId)ntohs((u_short)id);
            
            switch (id)
            {
            case PacketId::NONE:
                break;
			case LOGIN_RES:
				return BIND_HANDLER(LoginRes, buffer);
			case NOTIFY_ROOM_LIST:
				return BIND_HANDLER(NotifyRoomList, buffer);
			case ROOM_EVENT_RES:
				return BIND_HANDLER(RoomEventRes, buffer);
			case NOTIFY_PLAYER_LIST:
				return BIND_HANDLER(NotifyPlayerList, buffer);
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
		static bool LoginResPacketHandler(TSharedPtr<Session> session, TSharedPtr<LoginRes> packet);
		static bool NotifyRoomListPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyRoomList> packet);
		static bool RoomEventResPacketHandler(TSharedPtr<Session> session, TSharedPtr<RoomEventRes> packet);
		static bool NotifyPlayerListPacketHandler(TSharedPtr<Session> session, TSharedPtr<NotifyPlayerList> packet);
	};
}
