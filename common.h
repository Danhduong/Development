#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <cstdint>
#include <arpa/inet.h>

class Socket
{
    protected:
        int socketId;
    public:
        Socket(int socketId);
        ~Socket();
        Socket(Socket&&);
        Socket& operator=(Socket&&);
        Socket(Socket const&)               = delete;
        Socket& operator=(Socket const&)    = delete;

        virtual bool sendMessage(std::string const& buffer);
        bool getMessage(std::string& buffer);
};

class Client: public Socket
{
    public:
        Client(std::string const& host);
        virtual bool sendMessage(std::string const& buffer) override;
};

class Server: public Socket
{
    public:
        Server();
        Socket accept();
};

#endif