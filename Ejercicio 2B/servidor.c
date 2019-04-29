#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ejercicio2b.h"

float *f1_1_svc(void *vacio,struct svc_req *req) {
  char *args[]={"./EXEC",NULL};
  static float result;
	if(fork()==0)
        execvp(args[0],args);
	else {
		wait(NULL);
		printf("Me ejecute\n");
    result = 26;
    return (&result);
	}
}
