struct spectime{
    long tv_nsec;
    long tv_sec;
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
