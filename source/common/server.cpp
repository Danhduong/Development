#include "common.h"
#include "server.h"

string Server::Message;

void* Server::Task(void *arg)
{
	int n;
	int newsockfd = (long) arg;
	char msg[MAXPACKETSIZE];
	pthread_detach(pthread_self());
    
	while(1)
	{
		n = recv(newsockfd, msg, MAXPACKETSIZE,0);
		if(n == 0)
		{
		   close(newsockfd);
		   break;
		}
		msg[n] = 0;
		Message = string(msg);
    }

	return 0;
}

void Server::setup(int port)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
 	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);
	bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));
 	listen(sockfd, 5);
}

string Server::receive()
{
	string str;
	while(1)
	{
		socklen_t sosize  = sizeof(clientAddress);
		newsockfd = accept(sockfd,(struct sockaddr*)&clientAddress, &sosize);
		str = inet_ntoa(clientAddress.sin_addr);
		pthread_create(&serverThread, NULL, &Task, &newsockfd);
	}
	return str;
}

string Server::getMessage()
{
	return Message;
}

void Server::Send(string msg)
{
	send(newsockfd, msg.c_str(), msg.length(), 0);
}

void Server::clean()
{
	Message = "";
	memset(msg, 0, MAXPACKETSIZE);
}

void Server::detach()
{
	close(sockfd);
	close(newsockfd);
} 