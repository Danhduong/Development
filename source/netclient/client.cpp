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
	tcp.setup(argv[1], atoi(argv[2]));

	while(1)
	{
		tcp.Send("Danh Duong");
		tcp.Receive();
        sleep(1); /* second unit */
	}
	return 0;
}