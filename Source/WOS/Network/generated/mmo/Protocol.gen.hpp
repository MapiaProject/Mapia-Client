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
            *this >> uid >> mapName >> position;
        }
        virtual void Write() override
        {
            *this << uid << mapName << position;
            Finish();
        }
    public:
        String uid;
		String mapName;
		Vector2 position;
	
    };
    
    inline Packet& operator>>(Packet& pk, EnterMapReq& enterMapReq) {
        pk >> enterMapReq.uid >> enterMapReq.mapName >> enterMapReq.position;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const EnterMapReq& enterMapReq) {
        pk << enterMapReq.uid << enterMapReq.mapName << enterMapReq.position;
        return pk;
    }

	class Move
            : public Packet {
    public:
        Move() : Packet(static_cast<unsigned short>(PacketId::MOVE)) {
        }
        ~Move() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> dir;
        }
        virtual void Write() override
        {
            *this << dir;
            Finish();
        }
    public:
        Vector2 dir;
	
    };
    
    inline Packet& operator>>(Packet& pk, Move& move) {
        pk >> move.dir;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const Move& move) {
        pk << move.dir;
        return pk;
    }

	class Chat
            : public Packet {
    public:
        Chat() : Packet(static_cast<unsigned short>(PacketId::CHAT)) {
        }
        ~Chat() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> reinterpret_cast<uint16&>(type) >> targetUid >> message;
        }
        virtual void Write() override
        {
            *this << (type) << targetUid << message;
            Finish();
        }
    public:
        EChatType type;
		String targetUid;
		String message;
	
    };
    
    inline Packet& operator>>(Packet& pk, Chat& chat) {
        pk >> reinterpret_cast<uint16&>(chat.type) >> chat.targetUid >> chat.message;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const Chat& chat) {
        pk << (chat.type) << chat.targetUid << chat.message;
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
            *this >> isMine >> players;
        }
        virtual void Write() override
        {
            *this << isMine << players;
            Finish();
        }
    public:
        bool isMine;
		std::vector<PlayerInfo> players;
	
    };
    
    inline Packet& operator>>(Packet& pk, Spawn& spawn) {
        pk >> spawn.isMine >> spawn.players;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const Spawn& spawn) {
        pk << spawn.isMine << spawn.players;
        return pk;
    }

	class NotifyMove
            : public Packet {
    public:
        NotifyMove() : Packet(static_cast<unsigned short>(PacketId::NOTIFY_MOVE)) {
        }
        ~NotifyMove() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> position;
        }
        virtual void Write() override
        {
            *this << position;
            Finish();
        }
    public:
        Vector2 position;
	
    };
    
    inline Packet& operator>>(Packet& pk, NotifyMove& notifyMove) {
        pk >> notifyMove.position;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const NotifyMove& notifyMove) {
        pk << notifyMove.position;
        return pk;
    }

	class NotifyChat
            : public Packet {
    public:
        NotifyChat() : Packet(static_cast<unsigned short>(PacketId::NOTIFY_CHAT)) {
        }
        ~NotifyChat() {
    
        }
    protected:
        virtual void Read() override
        {
            Packet::Read();
            *this >> senderId >> message;
        }
        virtual void Write() override
        {
            *this << senderId << message;
            Finish();
        }
    public:
        String senderId;
		String message;
	
    };
    
    inline Packet& operator>>(Packet& pk, NotifyChat& notifyChat) {
        pk >> notifyChat.senderId >> notifyChat.message;
        return pk;
    }

    inline Packet& operator<<(Packet& pk, const NotifyChat& notifyChat) {
        pk << notifyChat.senderId << notifyChat.message;
        return pk;
    }

}
}
#pragma warning(pop)
