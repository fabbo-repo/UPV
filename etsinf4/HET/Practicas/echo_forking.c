/* 
 * echo_forking.c: servidor trivial de echo que atiende cada petición en un proceso distinto.
 *
 * Usage: echo_forking [port]
 *
 * Compilación:
 *   gcc -ggdb -m32 -fomit-frame-pointer -fno-stack-protector echo_forking.c -o echo_forking
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>
#include <string.h>

#define MAXBUF		1024

struct sockaddr_in self, client_addr;
int clientfd, sockfd, size;
int addrlen=sizeof(client_addr);

char global[1000];

int vulnerable (int fd){
	char buffer[32];
	/*---Echo back anything sent---*/

	size = recv(fd, buffer, MAXBUF, 0);
	memcpy(global, buffer, size);
	send(clientfd, buffer, size, 0);

	return 0;
}
int main(int argn, char *argv[]){
        int optval = 1;
	if (2 != argn ){
		printf("Usage: echo [port]\n");
		exit(-1);
	}
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("Socket");
		exit(errno);
	}
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
	
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(atoi(argv[1]));
	self.sin_addr.s_addr = INADDR_ANY;
	if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 ) {
		perror("Bind");
		exit(errno);
	}
	if ( listen(sockfd, 20) != 0 )	{
		perror("Listen");
		exit(errno);
	}
	system("echo -n 'Soy: ' ; id -un\n");
	printf("Esperando conecsiones al puerto: %d\n", atoi(argv[1]));
	while (1) {
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr,
				  &addrlen);
		printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr),
		       ntohs(client_addr.sin_port));

		/* Lee y retorna del socket cliente */
		if (0==fork()) {
		  // Proceso hijo
		  if (0==fork()) {
		    // Nieto. Este hace el trabajo.
		    vulnerable(clientfd);
		    shutdown(clientfd, SHUT_RDWR);
		    exit(0);
		  } else {
		    exit(0);       // El primer hijo muetro -> El nietro es heradado por init.
		  }
		}
		wait(NULL);  // El Proceso principal espera al hijo (impide que hayz zombies).
		close(clientfd);
		printf("%s:%d bye bye\n", inet_ntoa(client_addr.sin_addr),
		       ntohs(client_addr.sin_port));
	}
	return 0;
}


