#include "common.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstring>

Socket::Socket(int socketId) : socketId(socketId)
{
    if (socketId == -1)
    {
        std::stringstream message("Failed: socket()\n");
        message << strerror(errno);
        throw std::runtime_error(message.str());
    }
}

Socket::~Socket()
{
    if (socketId != -1)
    {
        ::close(socketId);
    }
}

Socket::Socket(Socket&& move) : socketId(move.socketId)
{
    move.socketId   = -1;
}

Socket& Socket::operator=(Socket&& move)
{
    std::swap(socketId, move.socketId);
    return *this;
}

bool Socket::sendMessage(std::string const& buffer)
{
    std::size_t size     = buffer.size() + 1;
    std::size_t sentSize = 0;
    while(sentSize != size)
    {
        std::size_t sent = ::write(socketId, buffer.data() + sentSize, size - sentSize);
        if (sent == -1u && errno == EINTR)
        {
            continue;
        }
        if (sent == -1u)
        {
            return false;
        }
        if (sent == 0)
        {
            return false;
        }
        sentSize += sent;
    }
    return true;
}

bool Socket::getMessage(std::string& buffer)
{
    buffer.clear();

    char tmp[1024];
    std::size_t get;
    while((get= ::read(socketId, tmp, sizeof(tmp))))
    {
        if (get == -1u && errno == EINTR)
        {
            continue;
        }
        if (get == -1u)
        {
            return false;
        }
        buffer.append(tmp, get);
    }
    return true;
}

Client::Client(std::string const& hostname) : Socket(::socket(PF_INET, SOCK_STREAM, 0))
{
    struct sockaddr_in serverAddr;
    socklen_t addrSize = sizeof(serverAddr);
    bzero((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(8080);
    serverAddr.sin_addr.s_addr  = inet_addr(hostname.c_str());

    if (::connect(socketId, (struct sockaddr*)&serverAddr, addrSize) != 0)
    {
        std::stringstream message("Failed: connect()\n");
        message << strerror(errno);
        throw std::runtime_error(message.str());
    }
}

bool Client::sendMessage(std::string const& buffer)
{
    bool result = Socket::sendMessage(buffer);
    if (result)
    {
        if (::shutdown(socketId, SHUT_WR) != 0)
        {
            std::stringstream message("Failed: shutdown()\n");
            message << strerror(errno);
            throw std::runtime_error(message.str());
        }
    }
    return result;
}

Server::Server() : Socket(::socket(PF_INET, SOCK_STREAM, 0))
{
    struct sockaddr_in serverAddr;
    bzero((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(8080);
    serverAddr.sin_addr.s_addr  = INADDR_ANY;

    if (::bind(socketId, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0)
    {
        std::stringstream message("Failed: bind()\n");
        message << strerror(errno);
        throw std::runtime_error(message.str());
    }

    if(::listen(socketId, 5) != 0)
    {
        std::stringstream message("Failed: listen()\n");
        message << strerror(errno);
        throw std::runtime_error(message.str());
    }
}

Socket Server::accept()
{
    struct  sockaddr_storage    serverStorage;
    socklen_t                   addr_size   = sizeof serverStorage;

    int newSocket = ::accept(socketId, (struct sockaddr*)&serverStorage, &addr_size);
    if (newSocket == -1)
    {
        std::cerr << fprintf(stdout, "%s\n%s\n", "Failed to accept", strerror(errno));
    }
    return Socket(newSocket);
}