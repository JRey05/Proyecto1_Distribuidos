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
#include <string.h>

#define BACKLOG 2


int main(int argc, char *argv[])
{
	/*La agencia A brinda turnos para sacar licencia de matrimonio, info sobre la partida de nacimiento y turno
		de inscripcion de bebe recien nacido, y la cantidad de atenciones realizadas hasta el momento*/

	/*La agencia B brinda turnos para patentar el auto, turnos para la transferencia de un vehiculo
		e informacion sobre el dominio de un vehiculo*/

	//	DATOS PARA LA CONEXION E ITERACIONES:
	/* Los mensajes de solicitud que se pueden recibir son: 
		"LicMatri" "PartiNac" "InscriBB" "CantAten"	
		"PateAuto" "TransfVe" "DomVehic"				*/

    if (argc != 2) { printf("\n\nUso: ./pt6cliente ipAgencia\n\n"); exit(0); }
    
    //capturo el ip de las agencias
	int MYPORT, nroagencia, opcion, otra;
	printf("\nBuen dia! Con que agencia se desea conectar?\n\n"); //para configurar el nro de puerto
	printf("1. Agencia A\n");
	printf("2. Agencia B\n\n");
	printf("Deseo la agencia nro: ");
	scanf("%i",&nroagencia);

	switch (nroagencia){
		case 1:{
			MYPORT=14550;
			break;
		}
		case 2:{
			MYPORT=14500;
			break;
		}
		default:{
			printf("Error: intente nuevamente con una opcion valida\n");
			exit(0);
		}
	}

	int deVuelta=1;
	char solicitud[9];
	char rta[9000];
	int sockAgencias, numbytes;
	int i,j;
	int newfd; /* las transferencias de datos se realizan mediante newfd */
    int sin_size; /* Contendra el tamaño de la escructura sockaddr_in */
	struct hostent *heAgencias; /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in their_addr; //dir ip y nro de puerto local
	struct sockaddr_in Agencias; /* dirección de la agencia A */
	if ((heAgencias=gethostbyname(argv[1])) == NULL)
	    { printf("Error en gethostbyname\n"); }

    while (deVuelta){
    // Asigna valores a la estruct their_addr para luego poder llamar a la función bind()
    their_addr.sin_family= AF_INET;
    their_addr.sin_port= htons(MYPORT); /*formato de network byte order */
    their_addr.sin_addr= *((struct in_addr *)heAgencias->h_addr); /* automaticamente usa IP local */
    bzero(&(their_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */

	/* Creamos el socket */
	if ((newfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{ printf("Error al crear el socket\n"); }
	

		printf("\nIngrese el nro de la opcion que desea:\n\n");
		printf("1. Consultar sobre turnos de la licencia de matrimonio\n");
		printf("2. Consultar sobre informacion de la partida de nacimiento\n");
		printf("3. Consultar sobre turno para inscripcion del recien nacido\n");
		printf("4. Consultar el numero de atenciones realizadas\n");
		printf("5. Consultar sobre turnos para patentar el auto\n");
		printf("6. Consultar sobre turnos para realizar la transferencia de un vehiculo\n");
		printf("7. Consultar informacion sobre el dominio de un vehiculo\n\n");
		printf("Ingresando la opcion nro: ");
		scanf("%i",&opcion);

		if (!((opcion==1)||(opcion==2)||(opcion==3)||(opcion==4)||(opcion==5)||(opcion==6)||(opcion==7))){
			printf("\nIntente nuevamente con un nro valido\n");
			printf("Adios! \n");
			exit(0);
		}

		switch(opcion){

			case 1: {
				printf("\n\nUsted ingreso la opcion 1) Turnos para Licencia de Matrimonio\n\n");
				strcpy(solicitud,"LicMatri");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
			case 2: {
				printf("\n\nUsted ingreso la opcion 2) Informacion sobre partidas de nacimiento\n\n");
				strcpy(solicitud,"PartiNac");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
			case 3: {
				printf("\n\nUsted ingreso la opcion 3) Turnos para la inscripcion de un bebe recien nacido\n\n");
				strcpy(solicitud,"InscriBB");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
			case 4: {
				printf("\n\nUsted ingreso la opcion 4) Cantidad de solicitudes atendidas hasta ahora\n\n");
				strcpy(solicitud,"CantAten");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
			case 5: {
				printf("\n\nUsted ingreso la opcion 5) Turnos para patentar el auto\n\n");
				strcpy(solicitud,"PateAuto");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
			case 6: {
				printf("\n\nUsted ingreso la opcion 6) Turnos para realizar la transferencia de un vehiculo\n\n");
				strcpy(solicitud,"TransfVe");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
			case 7: {
				printf("\n\nUsted ingreso la opcion 7) Informacion sobre el dominio de un vehiculo\n\n");
				strcpy(solicitud,"DomVehic");
				if (connect(newfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	    			{ printf("Error en connect\n"); }
				if (send(newfd, solicitud, sizeof(solicitud), 0) == -1)
					printf("Error en el send\n");
				break;
			}
		}
		if ((numbytes=recv(newfd, rta, sizeof(rta), 0)) == -1)
			{ printf("Error en receive\n"); }
		/* Visualizamos lo recibido */
		rta[sizeof(rta)] = '\0';
		printf("Respuesta:\n\n%s\n",rta);


		printf("Desea realizar otra operacion?\n");
		printf("1. Si!\n");
		printf("2. No, gracias\n\n");
		printf("Ingresando.. ");
		scanf("%i",&otra);
		switch (otra){
			case 1:{
				deVuelta=1;
				break;
			}
			case 2:{
				deVuelta=0;
				break;
			}
			default:{
				deVuelta=0;
				printf("\nAsumo que quizo decir que no..?\n");
				exit(0);
			}
		}

    close(newfd);
    }
    printf("\nAdios!\n");
    exit(0);
}
