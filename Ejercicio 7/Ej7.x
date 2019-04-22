struct spectime{
    time_t tv_sec;
    long tv_nsec;
};
struct respuesta{
    spectime tSv;
    long int t1;
};
program SYNCCLOCK{
    version VER1{
        struct respuesta sincronizar(spectime)=1; 
    } = 1;
} = 0x20004121;
