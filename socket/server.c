/* A simple echo server using TCP */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SERVER_TCP_PORT 3000	
#define BUFLEN	256	

int main() {
	int listenfd = 0, connfd = 0, len = 0;
	int sendtk = 0;
	struct sockaddr_in server, client, server2;
	char buf[BUFLEN], buftwo[BUFLEN];

	//토큰 받을 소켓, 커넥션 설정 <-- server로 작동//
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't create a socket\n");
		exit(1);
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(3000);
	server.sin_addr.s_addr = inet_addr("172.30.1.46");

	if ((bind(listenfd, (struct sockaddr*)&server, sizeof(server))) == -1) {
		fprintf(stderr, "fail to bind\n");
		exit(1);
	}
	//토큰 받기 기다림//
	listen(listenfd, 5);

	len = sizeof(client);
	connfd = accept(listenfd, (struct sockaddr*)&client, &len);
	memset(buf, 0x00, sizeof(buf));
	read(connfd, buf, sizeof(buf));
	//buf[strlen(buf)-1] = '\0';
	printf("received token :%s", buf);
	close(connfd);
	close(listenfd);
	//토큰 받고 해당 커넥션 종료//

	//토큰 전달할 소켓, 커넥션 생성 <-- client로 작동//
	if ((sendtk = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "fail to create tksocket\n");
		exit(1);
	}
	server2.sin_family = AF_INET;
	server2.sin_port = htons(1234);
	server2.sin_addr.s_addr = inet_addr("172.30.1.46");

	if (connect(sendtk, (struct sockaddr*)&server2, sizeof(server2)) == -1) {
		fprintf(stderr, "fail to connect to my client\n");
		exit(1);
	}

	write(sendtk, buf, strlen(buf));

	close(sendtk);

	return 0;
}
