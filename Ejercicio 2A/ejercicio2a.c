#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

double calcularTiempo(){
	struct timeval inicio,fin;
  	char *args[]={"./EXEC",NULL};
	gettimeofday(&inicio,NULL);
	double tiempo;
	if(fork()==0){
        execvp(args[0],args);
        exit(0);
    }
	else {
		wait(NULL);
		gettimeofday(&fin,NULL);
		tiempo = (double) ((fin.tv_sec * 1000000 - inicio.tv_sec * 1000000) + (fin.tv_usec - inicio.tv_usec));
	}
	return tiempo;
}

int main()
{
    //A null terminated array of character
    //pointers
    int i;
    double promedio=0;
    for(i=0;i<100;i++){
    	promedio=promedio+calcularTiempo();

	}
	promedio=promedio/100;
	printf("Tardo %.2f μs\n", (float)promedio);

	return 0;
}
