#include <sys/types.h>
#include <WinSock2.h>
#include <conio.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

int main(int argc, char *argv[])
{
	struct servent *servp;
	struct sockaddr_in server, remote;
	int request_sock, new_sock;

	int nfound, fd, maxfd, bytesread, addrlen;
	fd_set rmask, mask;

	char buf[BUFSIZ];
	if (argc != 2) {
		(void) fprintf(stderr,"usage: %s port\n",argv[0]);
		exit(1);
	}

	WSADATA info;
    if (WSAStartup(MAKEWORD(2,0), &info)) {
      throw "Could not start WSA";
    }

	if ((request_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		exit(1);
	}

	memset((void *) &server, 0, sizeof server);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons((u_short)atoi(argv[1]));
	if (bind(request_sock, (struct sockaddr *)&server, sizeof server) < 0) {
		perror("bind");
		exit(1);
	}
	if (listen(request_sock, SOMAXCONN) < 0) {
		perror("listen");
		exit(1);
	}

	FD_ZERO(&mask);
	FD_SET(request_sock, &mask);

	maxfd = request_sock;
	for (;;) {
		rmask = mask;
		nfound = select(maxfd+1, &rmask, (fd_set *)0, (fd_set *)0, NULL);
		if(nfound < 0)
		{
			/* something is very wrong! */
			perror("select");
			continue;
		}
		if (FD_ISSET(request_sock, &rmask)) {
			/* a new connection is available on the connetion socket */
			addrlen = sizeof(remote);
			new_sock = accept(request_sock,
				(struct sockaddr *)&remote, &addrlen);
			if (new_sock < 0) {
				perror("accept");
				exit(1);
			}
			printf("connection from host %s, port %d, socket %d\n",
				inet_ntoa(remote.sin_addr), ntohs(remote.sin_port),
				new_sock);
			fflush(stdout);

			FD_SET(new_sock, &mask);
			if (new_sock > maxfd)
				maxfd = new_sock;
			FD_CLR(request_sock, &rmask);
		}

		for (fd=0; fd <= maxfd ; fd++) {
			/* look for other sockets that have data available */
			if (FD_ISSET(fd, &rmask)) {
				/* process the data */
				bytesread = recv(fd, buf, sizeof buf - 1, 0);
				if (bytesread<0) {
					perror("read");
					/* fall through */
				}
				if (bytesread<=0) {
					printf("server: end of file on %d\n",fd);
					fflush(stdout);
					FD_CLR(fd, &mask);
					if (closesocket(fd)) perror("close");
					continue;
				}
				buf[bytesread] = '\0';
				printf("%d bytes from %d: %s\n",
					bytesread, fd, buf);
				fflush(stdout);
				
				/* echo it back */
				if (send(fd, buf, bytesread, 0)!= bytesread)
					perror("echo");
			}
		}
	}
	WSACleanup();
	return 0;
} /* main - wserverorg.c */
