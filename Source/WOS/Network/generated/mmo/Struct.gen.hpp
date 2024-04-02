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
#include "Enum.gen.hpp"
namespace gen {
namespace mmo {
    class Vector2
            : public Packet {
    public:
        Vector2() : Packet(static_cast<unsigned short>(PacketId::NONE)) {
        }
        ~Vector2() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> x >> y;
        }
        virtual void Write() override
        {
            *this << x << y;
            Finish();
        }
    public:
        float x;
		float y;
	
    };
    
    inline Packet& operator>>(Packet& pk, Vector2& vector2) {
        pk >> vector2.x >> vector2.y;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const Vector2& vector2) {
        pk << vector2.x << vector2.y;
        return pk;
    }

	class Vector3
            : public Packet {
    public:
        Vector3() : Packet(static_cast<unsigned short>(PacketId::NONE)) {
        }
        ~Vector3() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> x >> y >> z;
        }
        virtual void Write() override
        {
            *this << x << y << z;
            Finish();
        }
    public:
        float x;
		float y;
		float z;
	
    };
    
    inline Packet& operator>>(Packet& pk, Vector3& vector3) {
        pk >> vector3.x >> vector3.y >> vector3.z;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const Vector3& vector3) {
        pk << vector3.x << vector3.y << vector3.z;
        return pk;
    }

	class PlayerInfo
            : public Packet {
    public:
        PlayerInfo() : Packet(static_cast<unsigned short>(PacketId::NONE)) {
        }
        ~PlayerInfo() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> objectId >> position >> name;
        }
        virtual void Write() override
        {
            *this << objectId << position << name;
            Finish();
        }
    public:
        uint64 objectId;
		Vector2 position;
		String name;
	
    };
    
    inline Packet& operator>>(Packet& pk, PlayerInfo& playerInfo) {
        pk >> playerInfo.objectId >> playerInfo.position >> playerInfo.name;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const PlayerInfo& playerInfo) {
        pk << playerInfo.objectId << playerInfo.position << playerInfo.name;
        return pk;
    }

}
}
#pragma warning(pop)
