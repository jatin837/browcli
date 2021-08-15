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

	if (argc != 2)
		die("[USAGE: %s <server ip address>", argv[0]);

	int sockfd, n, sendbytes;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXLINE];

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("ERROR WHILE CREATING SOCKET!");



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
