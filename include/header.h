#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

using namespace std;

#define MAX_CLNT 	10

#define SERV_IP 	"127.0.0.1"
#define SERV_PORT	9190

typedef unsigned int UINT32;

class SocketTools{
public:
	int	clnt_fd[MAX_CLNT];

	int SockOpt(int serv_fd);
	int ServSockOpen();
	int ClntAccept(int);

	int Serv_Connect(); //서버 연걸 (클라이언트용)
};

//Client FD는 -1로 초기화 시켜주며 빈공간은 다시 -1로 변경 한다.
//ThreadID와ClntFD는 동시에 관리가 되어야 한다. 클라이언트가 접속하면 쓰레드는 무조건 생성 된다.
//Thrid의 idx와 clntfd의 idx는 동시에 관리 하면 thread id도 관리가 가능 할 것으로 보인다.
class cThreadDirect {
private:
	pthread_t 	ThrID[MAX_CLNT];
	int			ClntFD[MAX_CLNT];
	UINT32 		CurrClntCnt;
public: 
	cThreadDirect(){
		CurrClntCnt = -1;
		for(int idx = 0; idx <= MAX_CLNT; idx++){
			ThrID[idx] = -1;
			ClntFD[idx] = -1;
		}
		
		for(int idx = 0; idx <= MAX_CLNT; idx++){
			cout << "idx = " << idx << ", ThrID = " << ThrID[idx] << ", ClntFD = " << ClntFD[idx] << endl;
		}
	}

	//접속한 클라이언트의 유저 정보 처리 관련 function
	int AddUserInfo(int, pthread_t, int);
	int DeleteUserInfo();
	int StatusUserInfo();
};

typedef struct {
	int servfd;
	int clntfd;

	pthread_t tid[MAX_CLNT];
}t_HANDLE;


#endif
