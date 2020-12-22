#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_TCP_PORT 3000
#define BUFLEN	1000

int main(int argc, char** argv) {
	int sd = 0, tk = 0;
	int mycli_ser = 0, len = 0, new = 0;
	struct sockaddr_in server4, client4;
	char tk_buf[BUFLEN];
	struct sockaddr_in6 server6;
	char rbuf[BUFLEN];
	char ipv6_addr[16];
	char last[BUFLEN];

	//for ipv6 socket as client
	if ((sd = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't create 1st socket\n");
		exit(1);
	}

	server6.sin6_family = AF_INET6;
	server6.sin6_flowinfo = 0;
	server6.sin6_port = htons(50000);

	inet_pton(AF_INET6, "2001:0:53aa:64c:341f:5b82:3400:36f", (void*)&ipv6_addr);
	memcpy((void*)&server6.sin6_addr, (void*)&ipv6_addr, 16);


	//for ipv4 socket as server
	if ((tk = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "can't create 2nd socket\n");
		exit(1);
	}

	server4.sin_family = AF_INET;
	server4.sin_port = htons(1234);
	server4.sin_addr.s_addr = inet_addr("172.30.1.46");

	if (bind(tk, (struct sockaddr*)&server4, sizeof(server4)) == -1) {
		fprintf(stderr, "fail to binding\n");
		exit(1);
	}

	/* Connecting to the ipv6 server */
	if (connect(sd, (struct sockaddr*)&server6, sizeof(server6)) == -1) {
		fprintf(stderr, "Connection Fail\n");
		exit(1);
	}

	printf("Connected: server's address is %s\n", ipv6_addr);

	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);
	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);

	memset(rbuf, 0x00, sizeof(rbuf));
	read(0, rbuf, sizeof(rbuf));
	write(sd, rbuf, strlen(rbuf));

	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);
	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);

	memset(rbuf, 0x00, sizeof(rbuf));
	read(0, rbuf, sizeof(rbuf));
	write(sd, rbuf, strlen(rbuf));

	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);
	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);

	memset(rbuf, 0x00, sizeof(rbuf));
	read(0, rbuf, sizeof(rbuf));
	write(sd, rbuf, strlen(rbuf));

	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);
	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);

	memset(rbuf, 0x00, sizeof(rbuf));
	read(0, rbuf, sizeof(rbuf));
	write(sd, rbuf, strlen(rbuf));

	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);
	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);


	memset(rbuf, 0x00, sizeof(rbuf));
	read(0, rbuf, sizeof(rbuf));
	write(sd, rbuf, strlen(rbuf));

	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);
	memset(rbuf, 0x00, sizeof(rbuf));
	read(sd, rbuf, sizeof(rbuf));
	printf("%s", rbuf);

	memset(rbuf, 0x00, sizeof(rbuf));
	read(0, rbuf, sizeof(rbuf));
	write(sd, rbuf, strlen(rbuf));




	/////read from server4////
	//tk_buf[BUFLEN]
	listen(tk, 5);
	len = sizeof(client4);

	if ((new = accept(tk, (struct sockaddr*)&client4, &len)) == -1) {
		fprintf(stderr, "fail to accept\n");
		exit(1);
	}

	memset(tk_buf, 0x00, sizeof(tk_buf));
	read(new, tk_buf, sizeof(tk_buf));
	//printf("passed token from my server : %s and its len is %d\n",tk_buf,strlen(tk_buf));

	close(new);
	close(tk);
	//int wrote=0;
	//printf("tk_buf : %s and its len : %d\n",tk_buf,strlen(tk_buf));
	write(sd, tk_buf, strlen(tk_buf));
	//printf("i wrote %d bytes\n",wrote);
	memset(last, 0x00, sizeof(last));
	read(sd, last, sizeof(last));
	printf("%s", last);

	memset(last, 0x00, sizeof(last));
	read(sd, last, sizeof(last));
	printf("%s", last);
	close(sd);


	return(0);
}
