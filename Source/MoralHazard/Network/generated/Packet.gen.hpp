#pragma once

template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

namespace gen {
    enum PacketId : uint16 {
        NONE = 0,
		LOGIN_REQ = 1,
		ENTER_GAME_REQ = 2,
		ROOM_EVENT_REQ = 3,
		LOGIN_RES = 4,
		NOTIFY_ROOM_LIST = 5,
		ROOM_EVENT_RES = 6,
		NOTIFY_PLAYER_LIST = 7    
	};

}