#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#define PORT 14550 /* El puerto donde se conectara */
#define MAXDATASIZE 80

int main(int argc, char *argv[])
{
int sockfd, numbytes;
char buf[MAXDATASIZE]; /* Buffer donde se reciben los datos */
struct hostent *he; /* Se utiliza para convertir el nombre del host a su dirección IP */
struct sockaddr_in their_addr; /* dirección del server donde se conectara */
if (argc != 2) { printf("Error\n"); }
if ((he=gethostbyname(argv[1])) == NULL)
    { printf("Otro error\n"); }
/* Creamos el socket */
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    { printf("Error al crear el socket\n"); }

/* Establecemos their_addr con la dirección del server */
their_addr.sin_family = AF_INET;
their_addr.sin_port = htons(PORT);
their_addr.sin_addr = *((struct in_addr *)he->h_addr);
bzero(&(their_addr.sin_zero), 8);

/* Intentamos conectarnos con el servidor */
if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    { printf("Error en connect\n"); }
/* Recibimos los datos del servidor */
if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
    { printf("Error en receive\n"); }
/* Visualizamos lo recibido */
buf[numbytes] = '\0';
printf("Turnos disponibles para la licencia de matrimonio: %s\n",buf);
/* Devolvemos recursos al sistema */
close(sockfd);
return 0;
}
