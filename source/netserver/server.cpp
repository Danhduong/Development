#include "common.h"
#include "log.h"
#include "socket.h"
#include <signal.h>

Server tcp;

void sig_exit(int s)
{
    cout << "The program is exited with <" << s << "> signal" << endl;
	exit(0);
}

void *loop(void * m)
{
    pthread_detach(pthread_self());
	while(1)
	{
		srand(time(NULL));
		char ch = 'a' + rand() % 26;
		string s(1,ch);
		string str = tcp.getMessage();
		if( str != "" )
		{
			cout << "Message:" << str << endl;
			tcp.Send(" [client message: "+str+"] "+s);
			tcp.clean();
		}
		usleep(1000);
	}
	tcp.detach();
}

int main(int argc, char *argv[])
{
    cout << "Starting ... "<< endl;
    signal(SIGINT, sig_exit);
	tcp.setup(argv[1], atoi(argv[2]));
    tcp.receive();

	return 0;
}