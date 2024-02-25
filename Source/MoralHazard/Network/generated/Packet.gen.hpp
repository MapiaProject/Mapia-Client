#pragma once

template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

namespace gen {
    enum PacketId : uint16 {
        NONE = 0,
		LOGIN_REQ = 1,
		ENTER_GAME_REQ = 2,
		ENTER_ROOM_REQ = 3,
		ADD_ROOM_EVENT = 4,
		LOGIN_RES = 5,
		NOTIFY_ROOM_LIST = 6,
		ENTER_ROOM_RES = 7    
	};

}