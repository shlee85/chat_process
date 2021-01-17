#include "header.h"

/*
	앞으로 추가할 사항.
	1. 멀티 쓰레드를 위한 쓰레드ID관리.
	1-1. pthread_cancel, pthread_exit 차이점.
	2. 멀티 서버를 위한 클라이언트FD관리.
*/

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
pthread_t thrid;
void *t_func(void *data)
{
	static int retval = 0;

	char 	rbuf[1024] 	= {0,};
	int		ret 		= 0;

	cout << "Thread " << gidx << endl;

	//pthread_cancel()요청이 발생 하면 바로 종료 할 수 있다. ENABLE면 해당 루틴을 다 돌고 종료 할 수 있다.
	//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 

	while(1){
		ret = read(g_handle.clntfd, rbuf, sizeof(rbuf));
		cout << "ret is " << ret << "  strerror : " << strerror(errno) << endl;
		if(ret == 0){ //우아한 종료
			cout << "Client Closed" << endl;
			close(g_handle.clntfd);
		
			cout << "tid : " << g_handle.tid[0] << ", thrid : " << thrid << endl;
			//pthread_cancel(thrid);
			pthread_exit((void*)&retval);
		}
		else if(ret < 0){
			cout << "read fail : " << ret << " : " << strerror(errno) << endl;
			//continue;
		}
		cout << "Read Data : " << rbuf << endl;

		memset(rbuf, 0, sizeof(rbuf));
		sleep(1);
	}
}

int MainLoop()
{
	SocketTools Sock;
	cThreadDirect cThrManager;	//클래스를 호출 하면서 동시에 생성자 초기화를 진행 한다.

	fd_set 	allfds, readfds;
	
	int		maxfd;
	int 	idx = 0;
	int		thr_ret;

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
		
			cout << "접속처리 완료!!" << endl;
			gidx = idx;

			thr_ret = pthread_create(&g_handle.tid[idx], NULL, t_func, NULL);
			thrid = g_handle.tid[idx];

			/*
			유저 정보를 관리 하는 클래스 함수 추가.
				CurrClntCnt++; //현재 클라이언트 개수 체크.
			*/
			cThrManager.AddUserInfo(g_handle.clntfd, thrid, gidx); //접속 처리 된 유저 정보를 등록
			cout << endl << endl;
			cThrManager.StatusUserInfo();

			idx++;
//			pthread_join(thrid, NULL);

			FD_SET(g_handle.clntfd, &readfds);
			cout << endl;
		}

		sleep(1);
	}
	cout << "MainLoop Exit" << endl;

	return 1;
}

int main(int argc, char** argv)
{
	Init();	

	MainLoop();
}
