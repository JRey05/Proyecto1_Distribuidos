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

#define PORTCLI 14550 /* El puerto por donde se conectan clientes */
#define PORT_4LISTEN_AGB 14600 // puerto por donde escucha por transf de servicios desde la agencia B
#define PORT_4TRANSF_AGB 14650 // puerto por donde se le transfiere una consulta a la agencia B
#define BACKLOG 10

struct partidaDeNacimiento{
	struct tm fecha;
	char nombre[30];
	char apellido[30];
	unsigned long dni;
};

void atender1(int cantTurnosDisponiblesLicMatrimonio,struct tm *turnosDisponiblesLicMatrimonio,int newfd){

	int i;
	char turnosM[50][90];
	char i_c[4];
	for (i=0;i<cantTurnosDisponiblesLicMatrimonio;i++)
	{
			sprintf(i_c,"%u",i+1);
			strcat(i_c,". ");
			strcpy(turnosM[i],i_c);
			strcat(turnosM[i],asctime(&turnosDisponiblesLicMatrimonio[i]));
			//strcat(turnosM[i],"\n");
	}
	char mensajeMatrimonios[4150]; 

	for (i=0;i<50;i++)
		strcat(mensajeMatrimonios,turnosM[i]);
	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajeMatrimonios, sizeof(mensajeMatrimonios), 0) == -1)
    	{printf("Error en el send\n");}

}

void atender2(int cantDePartidasDeNacimiento,struct partidaDeNacimiento *partidasNac,int newfd){

	int i;
	char pdn[50][10000];
	//char dniBB[sizeof(unsigned long)];
	char fecha_c[80];
	char nombre_c[30];
	char apellido_c[30];
	char dni_c[sizeof(unsigned int)];
	char aux[1000];
	char i_c[4];
	for (i=0;i<cantDePartidasDeNacimiento;i++)
	{
			sprintf(i_c,"%u",i+1);
			strcat(i_c,". ");
			strcpy(aux,i_c);
			strcpy(fecha_c,asctime(&partidasNac[i].fecha));
			strcpy(nombre_c,partidasNac[i].nombre);
			strcpy(apellido_c,partidasNac[i].apellido);
			//dni_c contiene la transformacion de dni unsigned long -> string
			sprintf(dni_c, "%lu",partidasNac[i].dni);
			strcat(aux,nombre_c);
			strcat(aux," ");
			strcat(aux,apellido_c);
			strcat(aux,", ");
			strcat(aux,dni_c);
			strcat(aux,", ");
			strcat(aux,fecha_c);
			strcat(pdn[i],aux);

	}
	char mensajePNac[sizeof(pdn)];

	for (i=0;i<50;i++)
		strcat(mensajePNac,pdn[i]);

	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajePNac, sizeof(mensajePNac), 0) == -1)
    	printf("Error en el send\n");
}

void atender3(int cantTurnosDisponiblesInscripcionBebe,struct tm *turnosInscripcionBebe, int newfd){
	int i,j;
	char turnosBB[50][90];
    char i_c[4];
	for (i=0;i<cantTurnosDisponiblesInscripcionBebe;i++)
	{
			sprintf(i_c,"%u",i+1);
			strcat(i_c,". ");
			strcpy(turnosBB[i],i_c);
			strcat(turnosBB[i],asctime(&turnosInscripcionBebe[i]));
	}
	char mensajeBebes[4200]; //max: 50*80=4000 de las 50 struct tm + 50 de los saltos de linea agregados
	for (j=0;j<cantTurnosDisponiblesInscripcionBebe;j++)
			strcat(turnosBB[i],"\n");

	for (i=0;i<50;i++)
		strcat(mensajeBebes,turnosBB[i]);

	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajeBebes, 4000, 0) == -1)
    	printf("Error en el send\n");
}

void atender4(int atencionesRealizadas, int newfd){
	char mensajeNumAtenciones[60];
	char atenc[4];
	sprintf(atenc,"%u",atencionesRealizadas);
	strcpy(mensajeNumAtenciones,"Atenciones realizadas hasta ahora por la Agencia A: ");
	strcat (atenc,"\n");
	strcat(mensajeNumAtenciones,atenc);

	printf("Enviando la respuesta al cliente...\n");
	if (send(newfd, mensajeNumAtenciones, sizeof(mensajeNumAtenciones), 0) == -1)
		printf("Error en el send\n");
}

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
	int cantTurnosDisponiblesInscripcionBebe;
	struct partidaDeNacimiento partidasNac[50];
	int cantDePartidasDeNacimiento;
	int atencionesRealizadas=0;

	//	CARGO DATOS DE PRUEBA:
	time_t rawtime;
	struct tm turnoLM1,turnoLM2,turnoIBB1,turnoIBB2,fechaNBB1,fechaNac1,fechaNac2;
	struct partidaDeNacimiento pdn1,pdn2;

	turnoLM1.tm_sec=0;
	turnoLM1.tm_min=00;
	turnoLM1.tm_hour=15;
	turnoLM1.tm_mday=21;
	turnoLM1.tm_mon=5;
	turnoLM1.tm_year=119;
	turnoLM1.tm_wday=2;

	turnoLM2.tm_sec=0;
	turnoLM2.tm_min=30;
	turnoLM2.tm_hour=15;
	turnoLM2.tm_mday=18;
	turnoLM2.tm_mon=5;
	turnoLM2.tm_year=119;
	turnoLM2.tm_wday=4;

	turnoIBB1.tm_sec=0;
	turnoIBB1.tm_min=0;
	turnoIBB1.tm_hour=9;
	turnoIBB1.tm_mday=9;
	turnoIBB1.tm_mon=6;
	turnoIBB1.tm_year=119;
	turnoIBB1.tm_wday=1;

	turnoIBB2.tm_sec=0;
	turnoIBB2.tm_min=30;
	turnoIBB2.tm_hour=10;
	turnoIBB2.tm_mday=3;
	turnoIBB2.tm_mon=7;
	turnoIBB2.tm_year=119;
	turnoIBB2.tm_wday=2;

	fechaNac1.tm_sec=59;
	fechaNac1.tm_min=40;
	fechaNac1.tm_hour=20;
	fechaNac1.tm_mday=25;
	fechaNac1.tm_mon=3;
	fechaNac1.tm_year=119;
	fechaNac1.tm_wday=5;

	fechaNac2.tm_sec=54;
	fechaNac2.tm_min=15;
	fechaNac2.tm_hour=15;
	fechaNac2.tm_mday=06;
	fechaNac2.tm_mon=8;
	fechaNac2.tm_year=118;
	fechaNac2.tm_wday=0;

	turnosDisponiblesLicMatrimonio[0]=turnoLM1;
	turnosDisponiblesLicMatrimonio[1]=turnoLM2;
	cantTurnosDisponiblesLicMatrimonio++;
	cantTurnosDisponiblesLicMatrimonio++;

	turnosInscripcionBebe[0]=turnoIBB1;
	turnosInscripcionBebe[1]=turnoIBB2;
	cantTurnosDisponiblesInscripcionBebe++;
	cantTurnosDisponiblesInscripcionBebe++;

	pdn1.fecha=fechaNac1;
	strcpy(pdn1.nombre,"Joaquin");
	strcpy(pdn1.apellido,"Cerini");
	pdn1.dni=423390;
	partidasNac[0]=pdn1;
	cantDePartidasDeNacimiento++;

	pdn2.fecha=fechaNac2;
	strcpy(pdn2.nombre,"Lucia");
	strcpy(pdn2.apellido,"Montaner");
	pdn2.dni=411388;
	partidasNac[1]=pdn2;
	cantDePartidasDeNacimiento++;

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
	int sock_transf_agb; // y escucha las resoluciones de la agencia B por sock_transf_agb
	int sock_listen_agb; // por aca recibe la resolucion de la agencia B
	int newfd; /* las transferencias de datos se realizan mediante newfd */
	int newfd2; // para comunicarse con el servidor
    int sin_size; /* Contendra el tamaño de la escructura sockaddr_in */
	struct hostent *heAgenciaB; /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in my_addr; //dir ip y nro de puerto local
	struct sockaddr_in their_addr; /* dirección del cliente que solicito algo */
	struct sockaddr_in agb_transf;	// direccion de la agencia B
	struct sockaddr_in agb_listen;	// direccion de la agencia B (dif puerto)


    // Asigna valores a la estruct my_addr para luego poder llamar a la función bind()
    my_addr.sin_family= AF_INET;
    my_addr.sin_port= htons(PORTCLI); /*formato de network byte order */
    my_addr.sin_addr.s_addr= INADDR_ANY; /* automaticamente usa IP local */
    bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */

    if (argc != 2) { printf("\n\nUso: ./pt6AgenciaA ipAgenciaB\n\n"); exit(0);}
    //capturo el ip de la agencia b
	if ((heAgenciaB=gethostbyname(argv[1])) == NULL)
	    { printf("Error en gethostbyname\n"); }

    // Asigna valores a la estruct their_addr para luego poder llamar a la función bind()
    agb_transf.sin_family= AF_INET;
    agb_transf.sin_port= htons(PORT_4TRANSF_AGB); /*formato de network byte order */
    agb_transf.sin_addr= *((struct in_addr *)heAgenciaB->h_addr);
    bzero(&(agb_transf.sin_zero), 8); /* rellena con ceros el resto de la estructura */

    // Asigna valores a la estruct their_addr para luego poder llamar a la función bind()
    agb_listen.sin_family= AF_INET;
    agb_listen.sin_port= htons(PORT_4LISTEN_AGB); /*formato de network byte order */
    agb_listen.sin_addr= *((struct in_addr *)heAgenciaB->h_addr);
    bzero(&(agb_listen.sin_zero), 8); /* rellena con ceros el resto de la estructura */

	
	/* Creamos el socket */
	if ((sock_clientes = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{ printf("Error al crear el socket\n"); }
    if ((sock_transf_agb = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{ printf("Error al crear el socket 2\n"); }
    if ((sock_listen_agb = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	{ printf("Error al crear el socket 2\n"); }

    /* Asigna un nombre al socket */
    if (bind(sock_clientes, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
    	printf("Error en el bind\n");
    }

    if (bind(sock_listen_agb, (struct sockaddr *)&agb_listen, sizeof(struct sockaddr)) == -1) {
    	printf("Error en el 2do bind\n");
    }

    /* Habilita el socket para recibir conexiones, con una cola de x conexiones en espera como máximo */
    if (listen(sock_clientes, BACKLOG) == -1)
        printf("Ocurrio error en listen\n");
    if (listen(sock_listen_agb, BACKLOG) == -1)
        printf("Ocurrio error en listen\n");

    sin_size = sizeof(struct sockaddr_in);

    pid=fork();
    if (pid){
    	// en este proceso hijo escucha y atiende las consultas de la otra agencia
    	while(1){

	    	/*Se espera por conexiones desde la agencia b*/
	    	printf("\n-------------La Agencia A esta escuchando consultas de la Agencia B-------------\n\n");
	    	if ((newfd = accept(sock_listen_agb, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	        printf("Ocurrio error en accept\n");
	    	printf("Server: conexion desde la agencia b: %s\n", inet_ntoa(their_addr.sin_addr));
	    	printf("Desde puerto: %d \n", ntohs(their_addr.sin_port));
	    	if (!fork()){
	    		//hijo que atiende solicitudes
	    		if ((numbytes=recv(newfd, solicitud, sizeof(solicitud), 0)) == -1)
				{ printf("Error en receive\n"); }
				/* Visualizamos lo recibido */
				solicitud[sizeof(solicitud)] = '\0';
				printf("Solicitud recibida: %s\n",solicitud);

				//	CASOS QUE RESUELVE LA AGENCIA A
				int solicitudNro=checkSolicitudValida(solicitud);
				//printf ("\n\nSolicitud Nro Computado: %i\n\n",solicitudNro);
				switch(solicitudNro){

					case 1:{
						//	TURNOS LICENCIA DE MATRIMONIO
						atender1(cantTurnosDisponiblesLicMatrimonio,turnosDisponiblesLicMatrimonio,newfd);
				        break;

					}
					

					case 2:{

				        //	PARTIDAS DE NACIMIENTO
						atender2(cantDePartidasDeNacimiento,partidasNac,newfd);
				        break;
					}

					case 3:{

				    	//	TURNOS INSCRIPCION RECIEN NACIDO
						atender3(cantTurnosDisponiblesInscripcionBebe,turnosInscripcionBebe,newfd);
				        break;

					}		        	

					case 4:{

				        //	NUM ATENCIONES REALIZADAS
				        atender4(atencionesRealizadas,newfd);
				        break;
					}
		    	}
		    	exit(0);
	    	}
	    	//atencionesRealizadas++;			

	    }
	}
    else{	
    	while(1){

	    	//el proceso padre queda esperando por clientes y el hijo anterior por la agb
		    /*Se espera por conexiones de clientes*/
			printf("\n---------------La Agencia A esta escuchando consultas de clientes---------------\n\n");    
		    if ((newfd = accept(sock_clientes, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		        printf("Ocurrio error en accept\n");

		    printf("Server: conexion desde: %s\n", inet_ntoa(their_addr.sin_addr));
		    printf("Desde puerto: %d\n", ntohs(their_addr.sin_port));
		    if (!fork()){
		    	//hijo que se encarga de atender las solicitudes
		    	if ((numbytes=recv(newfd, solicitud, sizeof(solicitud), 0)) == -1)
				{ printf("Error en receive\n"); }
				/* Visualizamos lo recibido */
				solicitud[sizeof(solicitud)] = '\0';
				printf("Solicitud recibida: %s\n",solicitud);

				//	CASOS QUE RESUELVE LA AGENCIA A

				int solicitudNro=checkSolicitudValida(solicitud);
				//printf ("\n\nSolicitud Nro Computado: %i\n\n",solicitudNro);
				switch(solicitudNro){

					case 1:{
						//	TURNOS LICENCIA DE MATRIMONIO
						atender1(cantTurnosDisponiblesLicMatrimonio,turnosDisponiblesLicMatrimonio,newfd);
				        break;

					}
					

					case 2:{

				        //	PARTIDAS DE NACIMIENTO
						atender2(cantDePartidasDeNacimiento,partidasNac,newfd);
				        break;
					}

					case 3:{

				    	//	TURNOS INSCRIPCION RECIEN NACIDO
						atender3(cantTurnosDisponiblesInscripcionBebe,turnosInscripcionBebe,newfd);
				        break;

					}		        	

					case 4:{

				        //	NUM ATENCIONES REALIZADAS
				        atender4(atencionesRealizadas,newfd);
				        break;
					}

				//	CASOS A DELEGAR A LA AGENCIA B

					/*	En cada caso es necesario transferir el mensaje y esperar por la respuesta de la Agencia B */
					default:{

						// Asigna valores a la estruct their_addr para luego poder llamar a la función bind()
						agb_transf.sin_family= AF_INET;
						agb_transf.sin_port= htons(PORT_4TRANSF_AGB); /*formato de network byte order */
						agb_transf.sin_addr= *((struct in_addr *)heAgenciaB->h_addr);
						bzero(&(agb_transf.sin_zero), 8); /* rellena con ceros el resto de la estructura */
						if ((sock_transf_agb = socket(AF_INET, SOCK_STREAM, 0)) == -1)
							{ printf("Error al crear el socket 2\n"); }

						if (connect(sock_transf_agb, (struct sockaddr *)&agb_transf, sizeof(struct sockaddr)) == -1)
							{ printf("Error en connect\n"); }
				        if (send(sock_transf_agb, solicitud, sizeof(solicitud), 0) == -1)
				        	printf("Error en el send\n");
						if ((numbytes=recv(sock_transf_agb, infoTransferida, sizeof(infoTransferida), 0)) == -1)
							{ printf("Error en receive\n"); }
						printf("Rta desde la Agencia B: %s\n",infoTransferida);
						printf("Redirigiendo la respuesta al cliente...\n");
						// hay que enviarla al cliente
						if (send(newfd, infoTransferida, sizeof(infoTransferida), 0) == -1)
				        	printf("Error en el send\n");
						break;
					}
				}
				exit(0);
		    }
		    atencionesRealizadas++;	
	    }
    }

	close(newfd);
}
