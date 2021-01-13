#include "header.h"

t_HANDLE g_handle;

//소켓초기화 및 클라이언트 관리 초기화.
int Init()
{
	SocketTools Sock;
	
	cout << "Initizlize" << endl;
 
 	g_handle.servfd = Sock.ServSockOpen();

	return 1;
}

int DataProc()
{

	return 1;
}

int gidx;
void *t_func(void *data)
{
	char 	rbuf[1024] = {0,};

	cout << "Thread " << gidx << endl;

	read(g_handle.clntfd, rbuf, sizeof(rbuf));
	cout << "Read Data : " << rbuf << endl;
}

int MainLoop()
{
	SocketTools Sock;

	fd_set 	allfds, readfds;
	
	int		maxfd;
	int 	idx = 0;

	maxfd = g_handle.servfd;

	while(1){
		FD_ZERO(&readfds);
		FD_SET(g_handle.servfd, &readfds);

		allfds = readfds;

		cout << "select() 클라이언트 연결을 감지 중입니다." << endl;

		//소켓 변화를 감지 한다.
		if(select(maxfd+1, &allfds, 0, 0, NULL) == -1){
			cout << "select() error" << endl;
			cout << " : " << strerror(errno) << endl;

			return -1;
		}

		//서버 소켓의 변화가 있는 경우 동작.
		if(FD_ISSET(g_handle.servfd, &allfds)){
			g_handle.clntfd = Sock.ClntAccept(g_handle.servfd);

			cout << "접속!!" << endl;

			gidx = idx;
			pthread_create(&g_handle.tid[idx], NULL, t_func, NULL);
			idx++;

			FD_SET(g_handle.clntfd, &readfds);
			cout << endl;
		}


		sleep(1);
	}
	return 1;
}

int main(int argc, char** argv)
{
	Init();	

	MainLoop();
}
