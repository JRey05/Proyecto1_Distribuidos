#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>

int cantProcesos()
{
    struct rlimit rl;
    getrlimit(RLIMIT_NPROC, &rl);
    //ulimit -u En consola
    printf("\nCantidad de procesos que se pueden crear: %i\n", (int)rl.rlim_cur);
}

int main()
{
	long tiempo1,tiempo2,auxT1,tiempoFinal;
	struct timeval start, end;

	char str_end[100], str_read[100]; //utilizada para pasar el tiempo como string en el pipe

    int pipedes[2];
    pipe(pipedes);

	gettimeofday(&start, NULL);

	if (fork() == 0){
        //child
        gettimeofday(&end, NULL);
        tiempo1 =(long) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
        close(pipedes[0]);
        snprintf(str_end, 100, "%li", tiempo1);
        write(pipedes[1], str_end, strlen(str_end));

	}
	else {
        //father
        gettimeofday(&end, NULL);
        tiempo2 =(long) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
        


        wait(NULL);

        close(pipedes[1]);
        read(pipedes[0], str_read, 100);


        sscanf(str_read, "%li", &auxT1);

        if (auxT1<tiempo2){
            tiempoFinal=auxT1;
        }
        else {
            tiempoFinal=tiempo2;
        }
        printf("\nTiempo que se tardo en crear un proceso: %li ms\n",tiempoFinal);
        cantProcesos();
    }
    return 0;

}
