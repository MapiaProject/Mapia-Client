#pragma once

template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

namespace gen {
    enum PacketId : uint16 {
        NONE = 0,
    
	};

}