#include "Ej7.h"
#include <stdlib.h>
#include <rpc/rpc.h>
#include <time.h>
#include <stdio.h>

struct timespec tiempoSv;
clockid_t clk_id=CLOCK_REALTIME;
struct respuesta resultado;

struct respuesta * sincronizar_1_svc(spectime * tCli,struct svc_req *cliente){
    clock_gettime(clk_id, (&tiempoSv));
    resultado.t1 = (long) ((tiempoSv.tv_sec * 1000000000 + tiempoSv.tv_nsec) - (tCli->tv_sec * 1000000000 + tCli->tv_nsec));
    clock_gettime(clk_id, &(tiempoSv));
    resultado.tSv.tv_sec = (long) tiempoSv.tv_sec;
    resultado.tSv.tv_nsec = tiempoSv.tv_nsec;
    return (&resultado);
}
