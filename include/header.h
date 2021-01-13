#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

using namespace std;

#define MAX_CLNT 	10

#define SERV_IP 	"127.0.0.1"
#define SERV_PORT	9190

class SocketTools{
public:
	int	clnt_fd[MAX_CLNT];

	int SockOpt(int serv_fd);
	int ServSockOpen();
	int ClntAccept(int);

	int Serv_Connect(); //서버 연걸 (클라이언트용)
};

typedef struct {
	int servfd;
	int clntfd;
}t_HANDLE;


#endif
