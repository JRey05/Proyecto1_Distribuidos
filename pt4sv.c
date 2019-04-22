#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

    #define MYPORT 14550 /*Nro de puerto donde se conectaran los clientes*/
    #define BACKLOG 2 /* Tamaño de la cola de conexiones recibidas */

int main() {
    int sockfd; /* El servidor escuchara por sockfd */
    int newfd; /* las transferencias de datos se realizan mediante newfd */
    struct sockaddr_in my_addr; /* contendrá la dir IP y el nro de puerto local */
    struct sockaddr_in their_addr; /*Contendrá la dir IP y nro de puerto del cliente*/
    int sin_size; /* Contendra el tamaño de la escructura sockaddr_in */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("Ocurrio error en socket()\n");
    // Asigna valores a la estruct my_addr para luego poder llamar a la función bind()
    my_addr.sin_family= AF_INET;
    my_addr.sin_port= htons(MYPORT); /*formato de network byte order */
    my_addr.sin_addr.s_addr= INADDR_ANY; /* automaticamente usa IP local */
    bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */

    /* Asigna un nombre al socket */
    if ( bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {

    	printf("Error en el bind\n");
    }

    printf("Jon\n");

    /* Habilita el socket para recibir conexiones, con una cola de x conexiones en espera como máximo */
    if (listen(sockfd, BACKLOG) == -1)
        printf("Ocurrio error en listen\n");

    while(1) /* loop que llama a accept() */
    {
    sin_size = sizeof(struct sockaddr_in);


    /*Se espera por conexiones ,*/
    if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        printf("Ocurrio error en accept\n");

    printf("Server: conexion desde: %s\n", inet_ntoa(their_addr.sin_addr));
    printf("Desde puerto: %d \n", ntohs(their_addr.sin_port));
    if (!fork())
        { /* Comienza el proceso hijo, enviamos los datos mediante newfd */
        if (send(newfd, "Hello, world!\n", 14, 0) == -1)
        	printf("Error en el send\n");
        close(newfd);
        exit(0);
        }
    }
}
