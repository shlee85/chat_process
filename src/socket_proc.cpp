#include "header.h"

int SocketTools::SockOpt(int sockfd)
{
	cout << "Socket Option" << endl;

	socklen_t	optlen;
	int			option;

	optlen = sizeof(option);
	option = 1;

	/* bind error 방지. */
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);

	return 1;
}

int SocketTools::ServSockOpen()
{
	cout << "Socket Open" << endl;

	int 				serv_sock;
	struct sockaddr_in	serv_addr;

	memset(&serv_addr, 0, sizeof(sockaddr_in));

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1){
		cout << "socket() open fail" << endl;
		cout << " : " << strerror(errno) << endl;
		
		return -1;
	}

	cout << "Socket : " << serv_sock << endl;

	SockOpt(serv_sock);

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
		cout << "bind() error" << endl;
		cout << " : " << strerror(errno) << endl;

		return -1;
	}

	if(listen(serv_sock, 5) == -1){
		cout << "listen() error" << endl;
		cout << " : " << strerror(errno) << endl;

		return -1;
	}
	
	return serv_sock;
}

int SocketTools::ClntAccept(int serv_sock)
{
	cout << "Start Client Accept()" << endl;

	int 				clnt_size;
	int					clnt_sockfd;
	struct sockaddr_in	clnt_addr;

	memset(&clnt_addr, 0, sizeof(sockaddr_in));

	clnt_size = sizeof(clnt_addr);
	clnt_sockfd = accept(serv_sock, (struct sockaddr*)&clnt_addr, (socklen_t*)&clnt_size);
	if(clnt_sockfd == -1){
		cout << "accept() error" << endl;
		cout << " : " << strerror(errno) << endl;

		return -1;
	}

	cout << "Client Connect OK! FD : " << clnt_sockfd << endl;

	return clnt_sockfd;
}
