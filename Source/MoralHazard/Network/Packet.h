#pragma once

#include <vector>
#include <memory>
#include <span>

#ifdef __UNREAL__
using String = FString;
using StringView = FStringView;
#endif

class FSession;

class Packet {
    friend FSession;
public:
    Packet() = default;
    Packet(unsigned short id, int reserve = 1024);
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
        for(const T& elem : Data)
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
        for(unsigned short i = 0; i < len; ++i) {
            T t;
            *this >> t;
            Data.push_back(t);
        }
        return *this;
    }
protected:
    void virtual Write() {};
    void virtual Read();
    void Finish();
public:
    unsigned short GetId() const { return m_id; }
    unsigned short GetSize() const { return m_size; }
public:
    void Parse(std::span<char> buffer);

    template<class T>
    static TSharedPtr<T> ParseFrom(std::span<char> buffer)
    {
        auto pk = MakeShared<T>();
        pk->Parse(buffer);
        return pk;
    }
    std::vector<char>& Data();
private:
    std::vector<char> m_buffer;
    unsigned short m_id;
    unsigned short m_size;
};