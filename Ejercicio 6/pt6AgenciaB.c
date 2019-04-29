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

#define PORTCLI 14500 /* El puerto por donde se conectan clientes */
#define PORTCLIA 14550
#define PORT_4TRANSF_AGA 14600 // puerto por donde se le transfiere una consulta a la agencia B
#define BACKLOG 10

int checkSolicitudValida(char s[]){
	//no puedo usar switch case con strings en c...
	if(!strcmp(s,"LicMatri"))
		return 1;
	if(!strcmp(s,"PartiNac"))
		return 2;
	if(!strcmp(s,"InscriBB"))
		return 3;
	if(!strcmp(s,"CantAten"))
		return 4;
	if(!strcmp(s,"PateAuto"))
		return 5;
	if(!strcmp(s,"TransfVe"))
		return 6;
	if(!strcmp(s,"DomVehic"))
		return 7;
	return 0;
}


struct dominioVehiculo{
	char ciudad[30];
	char marca[20];
	char modelo[20];
	unsigned int nroMotorChasis;
};

void atender5(int cantTurnosPatentarAuto,struct tm *turnosPatentarAuto,int newfd){

	int i,j;
	char i_c[4];
    char turnosPatAuto[50][84];
	for (i=0;i<cantTurnosPatentarAuto;i++)
	{
		sprintf(i_c,"%u",i+1);
		strcat(i_c,". ");
		strcpy(turnosPatAuto[i],i_c);
		strcat(turnosPatAuto[i],asctime(&turnosPatentarAuto[i]));
	}
	char mensajePatAuto[4300]; //max: 50*80=4000 de las 50 struct tm + 50 de los saltos de linea agregados
	for (j=0;j<cantTurnosPatentarAuto;j++)
			strcat(turnosPatAuto[i],"\n");

	for (i=0;i<cantTurnosPatentarAuto;i++)
		strcat(mensajePatAuto,turnosPatAuto[i]);

	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajePatAuto, sizeof(mensajePatAuto), 0) == -1)
    	printf("Error en el send\n");

}

void atender6(int cantTurnosTransferenciaVehiculo,struct tm *turnosTransferenciaVehiculo,int newfd){

	int i,j;
	char turnosTransfVeh[50][84];
    char i_c[4];
	for (i=0;i<cantTurnosTransferenciaVehiculo;i++)
	{
		sprintf(i_c,"%u",i+1);
		strcat(i_c,". ");
		strcpy(turnosTransfVeh[i],i_c);
		strcat(turnosTransfVeh[i],asctime(&turnosTransferenciaVehiculo[i]));
	}
	char mensajeTransfAuto[4300]; //max: 50*80=4000 de las 50 struct tm + 50 de los saltos de linea agregados
	for (j=0;j<cantTurnosTransferenciaVehiculo;j++)
			strcat(turnosTransfVeh[i],"\n");

	for (i=0;i<cantTurnosTransferenciaVehiculo;i++)
		strcat(mensajeTransfAuto,turnosTransfVeh[i]);

	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajeTransfAuto, sizeof(mensajeTransfAuto), 0) == -1)
    	printf("Error en el send\n");
}

void atender7(int cantDominiosVeh,struct dominioVehiculo *dominiosVeh, int newfd){

	int i,j;
	char dm[50][112+sizeof(unsigned int)];
	char nro[sizeof(unsigned long)];
	char i_c[4];
	for (i=0;i<cantDominiosVeh;i++)
	{
		sprintf(i_c,"%u",i+1);
		strcat(i_c,". ");
		strcpy(dm[i],i_c);
		strcat(dm[i],dominiosVeh[i].ciudad);
		strcat(dm[i],", ");
		strcat(dm[i],dominiosVeh[i].marca);
		strcat(dm[i],",	");
		strcat(dm[i],dominiosVeh[i].modelo);
		strcat(dm[i],",	");
		//nro contiene la transformacion de dni unsigned long -> string
		sprintf(nro, "%u", dominiosVeh[i].nroMotorChasis);
		strcat(dm[i],nro);
		strcat(dm[i],"\n");
			
	}
	char mensajeDomVeh[sizeof(dm)]; 
	for (j=0;j<cantDominiosVeh;j++)
			strcat(dm[i],"\n");

	for (i=0;i<cantDominiosVeh;i++)
		strcat(mensajeDomVeh,dm[i]);

	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajeDomVeh, sizeof(mensajeDomVeh), 0) == -1)
    	printf("Error en el send\n");
}

int main(int argc, char *argv[])
{
	/*La agencia A brinda turnos para sacar licencia de matrimonio, info sobre la partida de nacimiento y turno
		de inscripcion de bebe recien nacido, y la cantidad de atenciones realizadas hasta el momento*/

	/*La agencia B brinda turnos para patentar el auto, turnos para la transferencia de un vehiculo
		e informacion sobre el dominio de un vehiculo*/

	// 	declaro las estructuras de la agencia
	//	manejo a los turnos como struct tm que tienen fecha y hora
	// 	la agencia lleva la cuenta de los turnos disponibles y de las partidas de nacimiento almacenadas
	struct tm turnosPatentarAuto[50];
	int cantTurnosPatentarAuto;
	struct tm turnosTransferenciaVehiculo[50];
	int cantTurnosTransferenciaVehiculo;
	struct dominioVehiculo dominiosVeh[50];
	int cantDominiosVeh;

	//	CARGO DATOS DE PRUEBA:

	struct tm turnoPAT1,turnoPAT2;
	struct tm turnoTRANSF1,turnoTRANSF2;
	
	turnoPAT1.tm_sec=0;
	turnoPAT1.tm_min=00;
	turnoPAT1.tm_hour=8;
	turnoPAT1.tm_mday=2;
	turnoPAT1.tm_mon=9;
	turnoPAT1.tm_year=119;
	turnoPAT1.tm_wday=4;

	turnoPAT2.tm_sec=0;
	turnoPAT2.tm_min=0;
	turnoPAT2.tm_hour=11;
	turnoPAT2.tm_mday=29;
	turnoPAT2.tm_mon=7;
	turnoPAT2.tm_year=119;
	turnoPAT2.tm_wday=2;

	turnoTRANSF1.tm_sec=0;
	turnoTRANSF1.tm_min=15;
	turnoTRANSF1.tm_hour=17;
	turnoTRANSF1.tm_mday=6;
	turnoTRANSF1.tm_mon=6;
	turnoTRANSF1.tm_year=119;
	turnoTRANSF1.tm_wday=3;

	turnoTRANSF2.tm_sec=0;
	turnoTRANSF2.tm_min=45;
	turnoTRANSF2.tm_hour=10;
	turnoTRANSF2.tm_mday=22;
	turnoTRANSF2.tm_mon=4;
	turnoTRANSF2.tm_year=119;
	turnoTRANSF2.tm_wday=5;

	turnosPatentarAuto[0]=turnoPAT1;
	turnosPatentarAuto[1]=turnoPAT2;
	cantTurnosPatentarAuto++;
	cantTurnosPatentarAuto++;

	turnosTransferenciaVehiculo[0]=turnoTRANSF1;
	turnosTransferenciaVehiculo[1]=turnoTRANSF2;
	cantTurnosTransferenciaVehiculo++;
	cantTurnosTransferenciaVehiculo++;

	struct dominioVehiculo dom1,dom2;
	strcpy(dom1.ciudad,"Santa Fe");
	strcpy(dom1.marca,"Fiat");
	strcpy(dom1.modelo,"Uno");
	dom1.nroMotorChasis=12783;
	strcpy(dom2.ciudad,"Corrientes");
	strcpy(dom2.marca,"Pontiac");
	strcpy(dom2.modelo,"Aztek");
	dom2.nroMotorChasis=23239;
	dominiosVeh[0]=dom1;
	dominiosVeh[1]=dom2;
	cantDominiosVeh++;
	cantDominiosVeh++;

	//	DATOS PARA LA CONEXION E ITERACIONES:
	/* Los mensajes de solicitud que se pueden recibir son: 
		"LicMatri" "PartiNac" "InscriBB" "CantAten"	
		"PateAuto" "TransfVe" "DomVehic"				*/

	char solicitud[9];
	char infoTransferida[9000];
	int numbytes;
	int pid;
	int i,j;
	int sock_clientes; // el sv escucha solicitudes de clientes por sock_clientes
	int sock_transf_aga; // y escucha las resoluciones de la agencia B por sock_transf_aga
	int newfd; /* las transferencias de datos se realizan mediante newfd */
    int sin_size; /* Contendra el tamaño de la escructura sockaddr_in */
	struct hostent *heAgenciaA; /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in my_addr; //dir ip y nro de puerto local
	struct sockaddr_in their_addr; /* dirección del cliente que solicito algo */
	struct sockaddr_in aga_transf;	// direccion de la agencia B

    // Asigna valores a la estruct my_addr para luego poder llamar a la función bind()
    my_addr.sin_family= AF_INET;
    my_addr.sin_port= htons(PORTCLI); /*formato de network byte order */
    my_addr.sin_addr.s_addr= INADDR_ANY; /* automaticamente usa IP local */
    bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */

    if (argc != 2) { printf("\n\nUso: ./pt6AgenciaB ipAgenciaA\n\n"); exit(0);}
    //capturo el ip de la agencia b
	if ((heAgenciaA=gethostbyname(argv[1])) == NULL)
	    { printf("Error en gethostbyname\n"); }

    // Asigna valores a la estruct their_addr para luego poder llamar a la función bind()
    /*
    aga_transf.sin_family= AF_INET;
    aga_transf.sin_port= htons(PORT_4TRANSF_AGA); //formato de network byte order
    aga_transf.sin_addr= *((struct in_addr *)heAgenciaA->h_addr);
    bzero(&(aga_transf.sin_zero), 8); // rellena con ceros el resto de la estructura
	*/
    // Asigna valores a la estruct their_addr para luego poder llamar a la función bind()
	
	/* Creamos el socket */
	if ((sock_clientes = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{ printf("Error al crear el socket\n"); }

    /* Asigna un nombre al socket */
    if (bind(sock_clientes, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
    	printf("Error en el bind\n");
    }

    /* Habilita el socket para recibir conexiones, con una cola de x conexiones en espera como máximo */
    if (listen(sock_clientes, BACKLOG) == -1)
        printf("Ocurrio error en listen\n");

    sin_size = sizeof(struct sockaddr_in);

	while(1){

    	//el proceso padre queda esperando por clientes y el hijo anterior por la agencia A
	    printf("\n---------------La Agencia B esta escuchando---------------\n\n");
	    /*Se espera por conexiones de clientes*/
	    if ((newfd = accept(sock_clientes, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	        printf("Ocurrio error en accept\n");

	    printf("Server: conexion desde: %s\n", inet_ntoa(their_addr.sin_addr));
	    printf("Desde puerto: %d \n", ntohs(their_addr.sin_port));
	    if (!fork()){

	    /* Comienza el proceso hijo que se encarga de atender las solicitudes, enviamos los datos mediante newfd */

	    	//	QUEDO A LA ESCUCHA DE UN MENSAJE, DEPENDIENDO EL MENSAJE, RESUELVO Y ENVIO, O DELEGO A LA AGENCIA B Y ENVIO LO QUE RECIBO DE ESTA
	    	if ((numbytes=recv(newfd, solicitud, sizeof(solicitud), 0)) == -1)
	    		{ printf("Error en receive\n"); }
			/* Visualizamos lo recibido */
			solicitud[sizeof(solicitud)] = '\0';
			printf("Solicitud recibida: %s\n",solicitud);

	    	//	CASOS QUE RESUELVE LA AGENCIA A

			int solicitudNro=checkSolicitudValida(solicitud);
			//printf ("\n\nSolicitud Nro Computado: %i\n\n",solicitudNro);
			switch(solicitudNro){

				case 5:{

					    	//	TURNOS PARA PATENTAR EL AUTO
					    	atender5(cantTurnosPatentarAuto,turnosPatentarAuto,newfd);
					        break;

						}		        	

						case 6:{


					        //	TURNOS PARA LA TRANSFERENCIA DEL VEHICULO
							atender6(cantTurnosTransferenciaVehiculo,turnosTransferenciaVehiculo,newfd);
					        break;

						}
						case 7:{
							//	INFO DEL DOMINIO DEL VEHICULO

							atender7(cantDominiosVeh,dominiosVeh,newfd);
					        break;
						}

	        //	CASOS A DELEGAR A LA AGENCIA A

				/*	En cada caso es necesario transferir el mensaje y esperar por la respuesta de la Agencia A */
				default:{

					aga_transf.sin_family= AF_INET;
				    aga_transf.sin_port= htons(PORTCLIA); /*formato de network byte order */
				    aga_transf.sin_addr= *((struct in_addr *)heAgenciaA->h_addr);
				    bzero(&(aga_transf.sin_zero), 8); /* rellena con ceros el resto de la estructura */


				    if ((sock_transf_aga = socket(AF_INET, SOCK_STREAM, 0)) == -1)
				    	{ printf("Error al crear el socket 2\n"); }

					if (connect(sock_transf_aga, (struct sockaddr *)&aga_transf, sizeof(struct sockaddr)) == -1)
						{ printf("Error en connect\n"); }
			        if (send(sock_transf_aga, solicitud, sizeof(solicitud), 0) == -1)
			        	printf("Error en el send\n");
	        		if ((numbytes=recv(sock_transf_aga, infoTransferida, sizeof(infoTransferida), 0)) == -1)
	    				{ printf("Error en receive\n"); }
	    			printf("Rta desde la Agencia A: %s\n",infoTransferida);
	    			printf("Redirigiendo la respuesta al cliente...\n");
	    			// hay que enviarla al cliente
	    			if (send(newfd, infoTransferida, sizeof(infoTransferida), 0) == -1)
			        	printf("Error en el send\n");
	    			break;
				}
	    	}	
	    exit(0);
	    }
	}	

    close(newfd);
}