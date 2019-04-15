#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
int main()
{
        //A null terminated array of character
        //pointers
	struct timeval inicio,fin;
  char *args[]={"./EXEC",NULL};
	gettimeofday(&inicio,NULL);
	if(fork()==0)
        execvp(args[0],args);
	else {
		wait(NULL);
		gettimeofday(&fin,NULL);
		double tiempo = (double) (fin.tv_usec - inicio.tv_usec);
		printf("Tardo %f microsegundos\n", (float)tiempo);
    return 0;
	}
}
