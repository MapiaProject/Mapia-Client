#include "Packet.h"
#include <winsock2.h>

Packet::Packet(uint16 id, PacketType type, int reserve) : m_buffer(2, 0), m_id(0) {
    if (type == RPC)
        id = 0x8000 | id;
    
    m_buffer.reserve(reserve);
    memcpy(m_buffer.data(), &id, sizeof(uint16));
}

std::vector<char>& Packet::Data() {
    return m_buffer;
}

void Packet::Parse(std::span<char> buffer) {
    m_buffer = std::vector(buffer.begin(), buffer.end());
    Read();
}

void Packet::Read() {
    *this >> m_id;
}

Packet& Packet::operator<<(unsigned char Data) {
    m_buffer.push_back(static_cast<char>(Data));
    return *this;
}

Packet& Packet::operator<<(unsigned short Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(unsigned int Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(unsigned long Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(unsigned long long Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(bool Data) {
    return *this << static_cast<unsigned char>(Data);
}

Packet& Packet::operator<<(char Data) {
    m_buffer.push_back(Data);
    return *this;
}

Packet& Packet::operator<<(short Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(int Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(long Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(long long Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(float Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(double Data) {
    char buffer[sizeof(Data)] = "";
    memcpy(buffer, &Data, sizeof(Data));
    m_buffer.insert(m_buffer.end(), buffer, buffer + sizeof(Data));
    return *this;
}

Packet& Packet::operator<<(StringView Data) {
    std::string str;
    str.assign(Data.begin(), Data.end());
    *this << static_cast<int16>(str.length());
    m_buffer.insert(m_buffer.end(), str.begin(), str.end());
    return *this;
}

Packet& Packet::operator>>(unsigned char& Data)
{
    Data = m_buffer.front();
    m_buffer.erase(m_buffer.begin());
    return *this;
}

Packet& Packet::operator>>(unsigned short& Data)
{
    std::memcpy(&Data, m_buffer.data(), sizeof(Data));
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + sizeof(Data));
    return *this;
}

Packet& Packet::operator>>(unsigned int& Data)
{
    std::memcpy(&Data, m_buffer.data(), sizeof(Data));
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + sizeof(Data));
    return *this;
}

Packet& Packet::operator>>(unsigned long& Data)
{
    std::memcpy(&Data, m_buffer.data(), sizeof(Data));
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + sizeof(Data));
    return *this;
}

Packet& Packet::operator>>(unsigned long long& Data)
{
    std::memcpy(&Data, m_buffer.data(), sizeof(Data));
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + sizeof(Data));
    return *this;
}

Packet& Packet::operator>>(bool& Data)
{
    unsigned char t;
    *this >> t;
    Data = static_cast<bool>(t);

    return *this;
}

Packet& Packet::operator>>(char& Data)
{
    unsigned char t;
    *this >> t;
    Data = static_cast<char>(t);

    return *this;
}

Packet& Packet::operator>>(short& Data)
{
    unsigned short t;
    *this >> t;
    Data = static_cast<short>(t);
    return *this;
}

Packet& Packet::operator>>(long& Data)
{
    unsigned long t;
    *this >> t;
    Data = static_cast<long>(t);
    return *this;
}

Packet& Packet::operator>>(long long& Data)
{
    unsigned long long t;
    *this >> t;
    Data = static_cast<long long>(t);
    return *this;
}

Packet& Packet::operator>>(int& Data)
{
    unsigned int t = 0;
    *this >> t;
    Data = static_cast<int>(t);
    return *this;
}

Packet& Packet::operator>>(float& Data)
{
    std::memcpy(&Data, m_buffer.data(), sizeof(Data));
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + sizeof(Data));
    return *this;
}

Packet& Packet::operator>>(double& Data)
{
    std::memcpy(&Data, m_buffer.data(), sizeof(Data));
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + sizeof(Data));
    return *this;
}

Packet& Packet::operator>>(String& Data)
{
    unsigned short len;
    *this >> len;
    std::string str(m_buffer.begin(), m_buffer.begin() + len);
    Data = FString(len, str.c_str());
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + len);
    return *this;
}