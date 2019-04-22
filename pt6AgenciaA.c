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

#define MYPORT 14550 /* El puerto donde se conectara */
#define BACKLOG 2
/*
enum dia {Lun,Mar,Mie,Jue,Vie};
enum mes {Ene,Feb,Marz,Abr,May,Jun,Jul,Ago,Sept,Oct,Nov,Dic};
enum hora {Manhana,Mediodia,Tarde};

struct turno{
	enum dia diaDeLaSemana;
	enum mes delMes;
	enum hora aLas; 
}turno_t;
*/

struct partidaDeNacimiento{
	struct tm fecha;
	char nombre[30];
	char apellido[30];
	unsigned long dni;
};

int main(int argc, char *argv[])
{
	/*La agencia A brinda turnos para sacar licencia de matrimonio, info sobre la partida de nacimiento y turno
		de inscripcion de bebe recien nacido, y la cantidad de atenciones realizadas hasta el momento*/

	/*La agencia B brinda turnos para patentar el auto, turnos para la transferencia de un vehiculo
		e informacion sobre el dominio de un vehiculo*/

	// 	declaro las estructuras de la agencia
	//	manejo a los turnos como struct tm que tienen fecha y hora
	// 	la agencia lleva la cuenta de los turnos disponibles y de las partidas de nacimiento almacenadas
	struct tm turnosDisponiblesLicMatrimonio[50];
	int cantTurnosDisponiblesLicMatrimonio;
	struct tm turnosInscripcionBebe[50];
	int cantTurnosDisponiblesInscipcionBebe;
	struct partidaDeNacimiento partidasNac[50];
	int cantDePartidasDeNacimiento;
	int atencionesRealizadas;

	//	CARGO DATOS DE PRUEBA
	time_t rawtime;
	struct tm *aux;
	time(&rawtime);
	aux=localtime(&rawtime);
	turnosDisponiblesLicMatrimonio[0]=*aux;
	cantTurnosDisponiblesLicMatrimonio++;


	int sockfd, numbytes;
	int i,j;
	int newfd; /* las transferencias de datos se realizan mediante newfd */
    int sin_size; /* Contendra el tamaño de la escructura sockaddr_in */
	struct hostent *he; /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in my_addr; //dir ip y nro de puerto local
	struct sockaddr_in their_addr; /* dirección de la agencia B */
	/*

	/* Creamos el socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{ printf("Error al crear el socket\n"); }

    // Asigna valores a la estruct my_addr para luego poder llamar a la función bind()
    my_addr.sin_family= AF_INET;
    my_addr.sin_port= htons(MYPORT); /*formato de network byte order */
    my_addr.sin_addr.s_addr= INADDR_ANY; /* automaticamente usa IP local */
    bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */

    /* Asigna un nombre al socket */
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {

    	printf("Error en el bind\n");
    }

    printf("Agencias are coming\n");

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



    	/* 	1ro envio los turnos de licencia de matrimonio,
    		2do envio turnos para la inscripcion del recien nacido
    		3ro las partidas de nacimiento
    		4to el num de atenciones realizadas
    	*/


    	//	QUEDO A LA ESCUCHA DE UN MENSAJE, DEPENDIENDO EL MENSAJE, RESUELVO Y ENVIO, O DELEGO A LA AGENCIA B Y ENVIO LO QUE RECIBO DE ESTA



    	//	CASOS QUE RESUELVE LA AGENCIA A



		    	//	TURNOS LICENCIA DE MATRIMONIO

		    	char turnosM[50][80];
		    	for (i=0;i<cantTurnosDisponiblesLicMatrimonio;i++)
		    	{
		    			strcpy(turnosM[i],asctime(&turnosDisponiblesLicMatrimonio[i]));
		    	}
		    	char mensajeMatrimonios[4050]; //max: 50*80=4000 de las 50 struct tm + 50 de los saltos de linea agregados
		    	for (j=0;j<cantTurnosDisponiblesLicMatrimonio;j++)
		    			strcat(turnosM[i],"\n");

		    	for (i=0;i<50;i++)
		    		strcat(mensajeMatrimonios,turnosM[i]);

		    	if (send(newfd, mensajeMatrimonios, 4000, 0) == -1)
		        	printf("Error en el send\n");


		        //	TURNOS INSCRIPCION RECIEN NACIDO

		        char turnosBB[50][80];
		    	for (i=0;i<cantTurnosDisponiblesInscipcionBebe;i++)
		    	{
		    			strcpy(turnosBB[i],asctime(&turnosInscripcionBebe[i]));
		    	}
		    	char mensajeBebes[4050]; //max: 50*80=4000 de las 50 struct tm + 50 de los saltos de linea agregados
		    	for (j=0;j<cantTurnosDisponiblesLicMatrimonio;j++)
		    			strcat(turnosBB[i],"\n");

		    	for (i=0;i<50;i++)
		    		strcat(mensajeBebes,turnosBB[i]);

		    	if (send(newfd, mensajeBebes, 4000, 0) == -1)
		        	printf("Error en el send\n");




		        //	PARTIDAS DE NACIMIENTO


				char pdn[50][80+60+sizeof(unsigned long)];
				char dniBB[sizeof(unsigned long)];
		    	for (i=0;i<cantDePartidasDeNacimiento;i++)
		    	{
		    			strcpy(pdn[i],asctime(&(partidasNac[i].fecha)));
		    			strcat(pdn[i],",	");
		    			strcat(pdn[i],partidasNac[i].nombre);
		    			strcat(pdn[i]," ");
		    			strcat(pdn[i],partidasNac[i].apellido);
		    			strcat(pdn[i],",	");

		    			//dniBB contiene la transformacion de dni unsigned long -> string
		    			sprintf(dniBB, "%lu", partidasNac[i].dni);
		    			strcat(pdn[i],dniBB);
		    			
		    	}
		    	char mensajePNac[sizeof(pdn)]; 
		    	for (j=0;j<cantDePartidasDeNacimiento;j++)
		    			strcat(pdn[i],"\n");

		    	for (i=0;i<50;i++)
		    		strcat(mensajePNac,pdn[i]);

		    	if (send(newfd, mensajePNac, sizeof(mensajePNac), 0) == -1)
		        	printf("Error en el send\n");




		        //	NUM ATENCIONES REALIZADAS

		        char mensajeNumAtenciones[10];
		        sprintf(mensajeNumAtenciones,"%i",atencionesRealizadas);
		        if (send(newfd, mensajeNumAtenciones, 10, 0) == -1)
		        	printf("Error en el send\n");


        //	CASOS A DELEGAR A LA AGENCIA B



        close(newfd);
        exit(0);
    	
    	*/
        }
    }
   }