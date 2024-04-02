#pragma once

namespace gen {
namespace mmo {
    template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

    enum PacketId : uint16 {
        NONE = 0,
		ENTER_GAME_REQ = 1,
		ENTER_MAP_REQ = 2,
		MOVE = 3,
		CHAT = 4,
		ENTER_GAME_RES = 5,
		SPAWN = 6,
		NOTIFY_MOVE = 7,
		NOTIFY_CHAT = 8    
	};

}
}