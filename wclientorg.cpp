#include <sys/types.h>
#include <WinSock2.h>	// header file for Win Sock
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <io.h>

int main(int argc, char *argv[])
{
	struct hostent *hostp;
	struct sockaddr_in server;
	int sock;

	fd_set rmask, mask;

	char buf[BUFSIZ];
	int bytesread;

	if (argc != 3) {
		(void) fprintf(stderr,"usage: %s port host\n",argv[0]);
		exit(1);
	}

	WSADATA info;
    if (WSAStartup(MAKEWORD(2,0), &info)) {
      throw "Could not start WSA";
    }

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		exit(1);
	}

	if ((hostp = gethostbyname(argv[2])) == 0) {
		fprintf(stderr,"%s: unknown host\n",argv[2]);
		exit(1);
	}
	memset((void *) &server, 0, sizeof server);
	server.sin_family = AF_INET;
	memcpy((void *) &server.sin_addr, hostp->h_addr, hostp->h_length);
	server.sin_port = htons((u_short)atoi(argv[1]));

	if (connect(sock, (struct sockaddr *)&server, sizeof server) < 0) {
		(void) close(sock);
		perror("connect");
		exit(1);
	}

	// waiting for two inputs : one from stdin, the other from sock
	FD_ZERO(&mask);
	FD_SET(sock, &mask);
	FD_SET(fileno(stdin), &mask);

	for (;;) {
		rmask = mask;
		if(select(FD_SETSIZE, &rmask, (fd_set *)0, (fd_set *)0, NULL) == 0)
		{
			perror("select error");
			continue;
		}
		
		if (FD_ISSET(fileno(stdin), &rmask)) {
			/* data from keyboard */

			if (!fgets(buf, sizeof buf, stdin)) {
				if (ferror(stdin)) {
					perror("stdin");
					exit(1);
				}
				exit(0);
			}
			if (send(sock, buf, strlen(buf), 0) < 0) {
				perror("write");
				exit(1);
			}
		}
		if (FD_ISSET(sock,&rmask)) {
			/* data from network */
			bytesread = recv(sock, buf, sizeof buf, 0);
			buf[bytesread] = '\0';
			printf("got %d bytes: %s\n", bytesread, buf);
			fflush(stdout);
		}
	}
	WSACleanup();  
	return 0;
} /* main - wclientorg.c */
