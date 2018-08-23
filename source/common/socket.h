#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

using namespace std;

#define MAX_PACKET_SIZE 4096

class Server
{
	public:
        int sockfd, newsockfd, n, pid;
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        pthread_t serverThread;
        char msg[MAX_PACKET_SIZE];
        static string Message;
        void setup(string address, int port);
        string receive();
        string getMessage();
        void Send(string msg);
        void detach();
        void clean();

	private:
        static void * Task(void * argv);
};

class Client
{
    private:
        int sock;
        std::string address;
        int port;
        struct sockaddr_in server;

    public:
        Client();
        bool setup(string address, int port);
        bool Send(string data);
        string receive(int size = 4096);
        string read();
        void exit();
};

#endif /* SERVER_H */