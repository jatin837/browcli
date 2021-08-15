#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 9003
#define MAXLINE 4096
#define SOCKADDR struct sockaddr


void die(const char* log_msg, ...); 


int main(int argc, char** argv){
	printf("DONE");
	if (argc != 2)
		die("[USAGE: %s <server ip address>]", argv[0]);

	printf("DONE");
	int sockfd, n, sendbytes;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXLINE];

	printf("DONE");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("ERROR WHILE CREATING SOCKET!");

	printf("DONE");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);

	printf("DONE");
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		die("inet_pton error for %s ", argv[1]);

	printf("DONE");
	if (connect(sockfd, (SOCKADDR*) &servaddr, sizeof(servaddr)) < 0)
		die("CONNECTION FAILED");

	printf("DONE");
	sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
	sendbytes = strlen(sendline);

	printf("DONE");
	if (write(sockfd, sendline, sendbytes) != sendbytes)
		die("WRITE ERROR");

	printf("DONE");
	memset(recvline, 0, MAXLINE);

	printf("DONE");
	
	printf("DONE");
	if (n < 0)
		die("READ ERROR");

	exit(0);

	return 0;
}


void die(const char* log, ...) {
	int errno_save;
	va_list ap;
	errno_save = errno;
	va_start(ap, log);
	vfprintf(stdout, log, ap);
	fprintf(stdout, "\n");
	fflush(stdout);

	if (errno_save != 0){
		fprintf(stdout, 
				"[ERROR NUMBER = %d] : %s\n", 
				errno_save,
				strerror(errno_save)
				);
		fprintf(stdout, "\n");
		fflush(stdout);
	}

	va_end(ap);

	exit(1);
}
