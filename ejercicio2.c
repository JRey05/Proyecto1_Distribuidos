#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
        //A null terminated array of character
        //pointers
	struct timeval inicio,fin;
        char *args[]={"./EXEC",NULL};
	gettimeofday(&inicio,NULL);
        execvp(args[0],args);
	wait(NULL);
	gettimeofdat(&fin,NULL);
	double tiempo = (double) (fin.tv_usec - inicio.tv_usec);



    return 0;
}
