#include "common.h"
#include "log.h"
#include "socket.h"
#include <signal.h>

Client tcp;

void sig_exit(int s)
{
	tcp.exit();
    cout << "The program is exited with <" << s << "> signal" << endl;
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_exit);

    cout << "Starting Client..." << endl;
	tcp.setup(argv[1], atoi(argv[2]));

	while(1)
	{
        cout << "Sending ..." << endl;
		tcp.Send("Danh Duong");
		string rec = tcp.receive(MAX_PACKET_SIZE);
		if(rec != "")
		{
			cout << "Server Response:" << rec << endl;
		}
		sleep(1);
	}
	return 0;
}