#include "common.h"
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>

int main()
{
    static std::string okMsg    = "OK";
    static std::string errorMsg = "ERROR";
    try
    {
        Server  server;
        int finished    = 0;
        while(!finished)
        {
            Socket connection = server.accept();

            std::string buffer;
            bool    ok = false;
            if (connection.getMessage(buffer))
            {
                std::cout << buffer << "\n" << "Message Complete\n";
                ok = true;
            }

            if (!connection.sendMessage(ok ? okMsg : errorMsg))
            {
                std::cerr << "Send Message Failed\n" << strerror(errno) << "\n";
            }
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        throw;
    }
}