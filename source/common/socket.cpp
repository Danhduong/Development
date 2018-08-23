#include "common.h"
#include "socket.h"

string Server::Message;

void* Server::Task(void *arg)
{
	int size = 0;
	int newsockfd = (long) arg;
	char msg[MAX_PACKET_SIZE];
	pthread_detach(pthread_self());
    
    cout << "Starting to receive message" << endl;
	while(1)
	{
		if((size = recv(newsockfd, msg, MAX_PACKET_SIZE, 0)) <= 0)
        {
		   close(newsockfd);
		   break;
		}
		msg[size] = 0;
		Message = string(msg);
        cout << "Sever : Recieving <" << msg << ">" << endl;
    }

	return 0;
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
    cout << "Send <" << data << ">" << endl;
    if(send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        cout << "Send failed : " << data << endl;
        return false;
    }

	return true;
}

string Client::receive(int size)
{
  	char buffer[size];
	memset(&buffer[0], 0, sizeof(buffer));

  	string reply;
	if(recv(sock , buffer , size, 0) < 0)
  	{
	    cout << "receive failed!" << endl;
		return nullptr;
  	}
	buffer[size-1]='\0';
  	reply = buffer;
  	return reply;
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