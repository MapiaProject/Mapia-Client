#pragma once

#include <vector>
#include <memory>
#include <span>

#include "ObjectPool.h"

#ifdef __UNREAL__
using String = FString;
using StringView = FStringView;
#endif

class FSession;

enum PacketType : uint8
{
    Generated,
    RPC
};

class Packet {
    friend FSession;
public:
    Packet() = default;
    Packet(uint16 id, PacketType type = Generated, int reserve = 1024);
    virtual ~Packet() {};
public:
    Packet& operator<<(unsigned char Data);
    Packet& operator<<(unsigned short Data);
    Packet& operator<<(unsigned int Data);
    Packet& operator<<(unsigned long Data);
    Packet& operator<<(unsigned long long Data);
    Packet& operator<<(bool Data);
    Packet& operator<<(char Data);
    Packet& operator<<(short Data);
    Packet& operator<<(int Data);
    Packet& operator<<(long Data);
    Packet& operator<<(long long Data);
    Packet& operator<<(float Data);
    Packet& operator<<(double Data);
    Packet& operator<<(StringView Data);

    template<class T>
    Packet& operator<<(std::vector<T> Data) {
        *this << static_cast<unsigned short>(Data.size());
        for (const T& elem : Data)
            *this << elem;
        return *this;
    }
public:
    Packet& operator>>(long long& Data);
    Packet& operator>>(unsigned char& Data);
    Packet& operator>>(unsigned short& Data);
    Packet& operator>>(unsigned int& Data);
    Packet& operator>>(unsigned long& Data);
    Packet& operator>>(unsigned long long& Data);
    Packet& operator>>(bool& Data);
    Packet& operator>>(char& Data);
    Packet& operator>>(short& Data);
    Packet& operator>>(int& Data);
    Packet& operator>>(long& Data);
    Packet& operator>>(float& Data);
    Packet& operator>>(double& Data);
    Packet& operator>>(String& Data);

    template<class T>
    Packet& operator>>(std::vector<T>& Data) {
        unsigned short len;
        *this >> len;
        for (unsigned short i = 0; i < len; ++i) {
            T t;
            *this >> t;
            Data.push_back(t);
        }
        return *this;
    }
protected:
    void virtual Write() {};
    void virtual Read();
public:
    void SetId(uint16 id) { m_id = id; }
    unsigned short GetId() const { return m_id; }
public:
    void Parse(std::span<char> buffer);

    template<class T>
    static TSharedPtr<T> ParseFrom(std::span<char> buffer, uint16 id)
    {
        auto pk = new T;
        pk->Parse(buffer);
        pk->SetId(id);
        return TSharedPtr<T>(pk);
    }
    static bool IsRpcId(uint16 id);

    std::vector<char>& Data();

    void Reset();
private:
    std::vector<char> m_buffer;
    unsigned short m_id;
};
