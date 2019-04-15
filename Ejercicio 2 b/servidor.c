#include <stdio.h>
#include "ejercicio2b.h"

float * f1_1(void *vacio,struct svc_req *req) {
  char *args[]={"./EXEC",NULL};
  static float result;
	if(fork()==0)
        execvp(args[0],args);
	else {
		wait(NULL);
		printf("Me ejecute\n", (float)tiempo);
    result = 0;
    return (&result);
	}
}
