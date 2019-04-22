#include "Ej7.h" 
#include <stdlib.h>
#include <rpc/rpc.h>
#include <time.h>
#include <stdio.h>
long int diferencia;
spectime * actual;
clockid_t clk_id=CLOCK_REALTIME;
struct respuesta resultado;
struct respuesta * sincronizar_1_svc(struct timespec * tCli,struct svc_req *cliente){
    if(!clock_gettime(clk_id, actual)) {
        printf("Error");
        exit(1);    
    }
    resultado.t1 = (long) ((actual->tv_sec * 1000000000 + actual->tv_nsec) - (tCli->tv_sec * 1000000000 + tCli->tv_nsec));
    clock_gettime(clk_id, &(resultado.tSv));
    return (&resultado);
}
