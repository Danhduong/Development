#include "common.h"
#include "socket.h"

string Server::Message;

void* Server::Task(void *arg)
{
	int size = 0;
	char msg[MAX_PACKET_SIZE];
    int fd = (long)arg;
	pthread_detach(pthread_self());

    cout << "Reading on [" << fd << "] socket" << endl;
	while(1)
	{
		if((size = recv(fd, msg, MAX_PACKET_SIZE, 0)) > 0)
        {
            msg[size] = 0;
            Message = string(msg);
            cout << "[" << fd << "] Message = [" << Message << "]" << endl;
            send(fd, "OK", strlen("OK"), 0);
		}
    }
    pthread_exit(NULL);
	return NULL;
}

void Server::setup(string address, int port)
{
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      	cout << "Could not create socket" << endl;
    }

 	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(address.c_str());
	serverAddress.sin_port = htons(port);

    cout << "[" << sockfd << "] Server is <" << address.c_str() << ":" << port << ">" << endl;

	if(bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "Error on Binding";
    }
 	listen(sockfd, 5);
}

string Server::receive()
{
	string str;
    int port = 0;
    
	while(1)
	{
		socklen_t sosize  = sizeof(clientAddress);
		newsockfd = accept(sockfd,(struct sockaddr*)&clientAddress, &sosize);
		str = inet_ntoa(clientAddress.sin_addr);
        port = ntohs(clientAddress.sin_port);
        cout << "[" << newsockfd << "] Client is [" << str << ":" << port << "]" << endl;
		if(pthread_create(&serverThread, NULL, &Task, (void *)newsockfd) != 0)
        {
            cout << "Cannot create thread...";
            return NULL;
        }
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
	memset(msg, 0, MAX_PACKET_SIZE);
}

void Server::detach()
{
	close(sockfd);
	close(newsockfd);
}

Client::Client()
{
    sock = -1;
}

bool Client::setup(string address , int port)
{
    if((sock = socket(AF_INET , SOCK_STREAM , 0)) < 0)
    {
      	cout << "Could not create socket" << endl;
        return false;
    }
    cout << "[" << sock << "] Client is <" << address.c_str() << ":" << port << ">" << endl;

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr(address.c_str());
  	server.sin_family = AF_INET;
  	server.sin_port = htons(port);

  	if(connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  	{
        perror("connect failed. Error");
        return false;
  	}
  	return true;
}

bool Client::Send(string data)
{
    cout << "Sending <" << data << ">" << endl;
    if(send(sock, data.c_str(), strlen(data.c_str()), 0) < 0)
    {
        cout << "Send failed : " << data << endl;
        return false;
    }
	return true;
}

bool Client::Receive()
{
  	char buffer[MAX_PACKET_SIZE];

	memset(&buffer[0], 0, sizeof(buffer));

	if(recv(sock , buffer , MAX_PACKET_SIZE, 0) > 0)
  	{
        buffer[strlen(buffer)] = '\0';
        cout << "Server response : [" << buffer << "]" << endl;
        return true;
  	}
	return false;
}

string Client::read()
{
  	char buffer[1] = {};
  	string reply;
  	while (buffer[0] != '\n')
    {
        if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
        {
            cout << "receive failed!" << endl;
            return nullptr;
        }
		reply += buffer[0];
	}
	return reply;
}

void Client::exit()
{
    close( sock );
}