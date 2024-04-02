#pragma once
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 4100)
#include "Packet.gen.hpp"

#ifdef __UNREAL__
#include "Network/Packet.h"
#elif __SERVER__
#include "Network/Packet.hpp"
#include "Util/Types.hpp"
#endif

#include <vector>

#undef ERROR

/* Additional headers. */

namespace gen {
namespace mmo {
    enum EEntityType : uint16 {
        Player,
		Monster
    };
	enum EChatType : uint16 {
        Direct,
		Party,
		All
    };
}
}
#pragma warning(pop)
