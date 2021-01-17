#include "header.h"

int cThreadDirect::AddUserInfo(int clntfd, pthread_t tid, int idx)
{
	CurrClntCnt++;

	ClntFD[idx] = clntfd;
	ThrID[idx] = tid;

	return 1;
}

int cThreadDirect::DeleteUserInfo()
{
	CurrClntCnt--;

	return 1;
}

int cThreadDirect::StatusUserInfo()
{
	for(int idx = 0; idx <= MAX_CLNT; idx++){
		cout << "idx = " << idx << ", ThrID = " << ThrID[idx] << ", ClntFD = " << ClntFD[idx] << endl;
	}

	return 1;
}
