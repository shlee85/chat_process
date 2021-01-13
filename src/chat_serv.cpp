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

int MainLoop()
{
	SocketTools Sock;

	while(1){
		cout << "Connection Waiting..........." << endl;
		g_handle.clntfd = Sock.ClntAccept(g_handle.servfd);
		sleep(1);
	}
	return 1;
}

int main(int argc, char** argv)
{
	Init();	

	MainLoop();
}
