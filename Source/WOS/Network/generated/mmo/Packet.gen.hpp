#pragma once

namespace gen {
namespace mmo {
    template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

    enum PacketId : uint16 {
        NONE = 0,
		ENTER_GAME_REQ = 1    
	};

}
}