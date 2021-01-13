#include "header.h"
//#include "stdio.h"
#include <cstdio>

int DataProc(int clntfd)
{
	char 	sbuf[1024] = {0,};

	snprintf(sbuf, 1024-1, "HI SHLEE TEST PROGRAM");
	
	cout << "Send Buf : " << sbuf << endl;

	send(clntfd, sbuf, strlen(sbuf), 0);

	return 1;
}

int SocketTools::Serv_Connect()
{
	int 				serv_sock;
	struct sockaddr_in	sock_addr;

	int 				arg;
	int					on = 1;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1){
		cout << "socket error" << endl;
		cout << " : " << strerror(errno) << endl;

		return -1;
	}

	memset(&sock_addr, 0, sizeof(sock_addr));

	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr(SERV_IP);
	sock_addr.sin_port = htons(SERV_PORT);

	if(connect(serv_sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1){
		cout << "connect error : " << endl;
		cout << " : " << strerror(errno) << endl;

		return -1;
	}

	cout << "Client Connect OK" << endl;
	
	return serv_sock;
}

int main(int argc, char* argv[])
{
	int clntfd;

	SocketTools socket;

	clntfd = socket.Serv_Connect();
	DataProc(clntfd);

	return 1;
}
