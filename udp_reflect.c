#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>


#define SERV_PORT		(8888)
#define MAXLINE			(2048)

void dg_echo(int sockfd, struct sockaddr_in* pcliaddr, int clilen) {
	int n;
	int len;
	char buf[MAXLINE];

	for(;;) {
		len = clilen;
		n = recvfrom(sockfd, buf, MAXLINE, 0, pcliaddr, &len);
		sendto(sockfd, buf, n, 0, pcliaddr, len);
	}
}



int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(sockfd, (struct sockaddr_in*)&servaddr, sizeof(servaddr));

	dg_echo(sockfd, (struct sockaddr_in*)&cliaddr, sizeof(cliaddr));

}