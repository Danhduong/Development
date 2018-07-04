#include "common.h"
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: client <host> <Message>\n";
        exit(1);
    }

    try
    {
        Client  client(argv[1]);

        if (!client.sendMessage(argv[2]))
        {
            std::stringstream message("Failed: sendMessage()\n");
            message << strerror(errno);
            throw std::runtime_error(message.str());
        }

        std::string     buffer;
        if (client.getMessage(buffer))
        {
            std::cout << "Response from server: " << buffer << "\n";
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        throw;
    }
}