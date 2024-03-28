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
#include "Struct.gen.hpp"
namespace gen {
namespace mmo {
    class EnterGameReq
            : public Packet {
    public:
        EnterGameReq() : Packet(static_cast<unsigned short>(PacketId::ENTER_GAME_REQ)) {
        }
        ~EnterGameReq() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            
        }
        virtual void Write() override
        {
            
            Finish();
        }
    public:
        
    };
    
    inline Packet& operator>>(Packet& pk, EnterGameReq& enterGameReq) {
        
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const EnterGameReq& enterGameReq) {
        
        return pk;
    }

}
}
#pragma warning(pop)
