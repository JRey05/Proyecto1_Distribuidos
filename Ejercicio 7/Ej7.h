/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _EJ7_H_RPCGEN
#define _EJ7_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct spectime {
	long tv_nsec;
	long tv_sec;
};
typedef struct spectime spectime;

struct respuesta {
	spectime tSv;
	long t1;
};
typedef struct respuesta respuesta;

#define SYNCCLOCK 0x20004121
#define VER1 1

#if defined(__STDC__) || defined(__cplusplus)
#define sincronizar 1
extern  struct respuesta * sincronizar_1(spectime *, CLIENT *);
extern  struct respuesta * sincronizar_1_svc(spectime *, struct svc_req *);
extern int syncclock_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define sincronizar 1
extern  struct respuesta * sincronizar_1();
extern  struct respuesta * sincronizar_1_svc();
extern int syncclock_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_spectime (XDR *, spectime*);
extern  bool_t xdr_respuesta (XDR *, respuesta*);

#else /* K&R C */
extern bool_t xdr_spectime ();
extern bool_t xdr_respuesta ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_EJ7_H_RPCGEN */