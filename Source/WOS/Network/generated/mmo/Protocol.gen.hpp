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
            *this >> uid;
        }
        virtual void Write() override
        {
            *this << uid;
            Finish();
        }
    public:
        String uid;
	
    };
    
    inline Packet& operator>>(Packet& pk, EnterGameReq& enterGameReq) {
        pk >> enterGameReq.uid;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const EnterGameReq& enterGameReq) {
        pk << enterGameReq.uid;
        return pk;
    }

	class EnterMapReq
            : public Packet {
    public:
        EnterMapReq() : Packet(static_cast<unsigned short>(PacketId::ENTER_MAP_REQ)) {
        }
        ~EnterMapReq() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> uid >> mapName;
        }
        virtual void Write() override
        {
            *this << uid << mapName;
            Finish();
        }
    public:
        String uid;
		String mapName;
	
    };
    
    inline Packet& operator>>(Packet& pk, EnterMapReq& enterMapReq) {
        pk >> enterMapReq.uid >> enterMapReq.mapName;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const EnterMapReq& enterMapReq) {
        pk << enterMapReq.uid << enterMapReq.mapName;
        return pk;
    }

	class EnterGameRes
            : public Packet {
    public:
        EnterGameRes() : Packet(static_cast<unsigned short>(PacketId::ENTER_GAME_RES)) {
        }
        ~EnterGameRes() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> success;
        }
        virtual void Write() override
        {
            *this << success;
            Finish();
        }
    public:
        bool success;
	
    };
    
    inline Packet& operator>>(Packet& pk, EnterGameRes& enterGameRes) {
        pk >> enterGameRes.success;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const EnterGameRes& enterGameRes) {
        pk << enterGameRes.success;
        return pk;
    }

	class Spawn
            : public Packet {
    public:
        Spawn() : Packet(static_cast<unsigned short>(PacketId::SPAWN)) {
        }
        ~Spawn() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> players;
        }
        virtual void Write() override
        {
            *this << players;
            Finish();
        }
    public:
        std::vector<PlayerInfo> players;
	
    };
    
    inline Packet& operator>>(Packet& pk, Spawn& spawn) {
        pk >> spawn.players;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const Spawn& spawn) {
        pk << spawn.players;
        return pk;
    }

	class EnterMapRes
            : public Packet {
    public:
        EnterMapRes() : Packet(static_cast<unsigned short>(PacketId::ENTER_MAP_RES)) {
        }
        ~EnterMapRes() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> success;
        }
        virtual void Write() override
        {
            *this << success;
            Finish();
        }
    public:
        bool success;
	
    };
    
    inline Packet& operator>>(Packet& pk, EnterMapRes& enterMapRes) {
        pk >> enterMapRes.success;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const EnterMapRes& enterMapRes) {
        pk << enterMapRes.success;
        return pk;
    }

}
}
#pragma warning(pop)
