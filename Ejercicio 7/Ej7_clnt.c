/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "Ej7.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

struct respuesta *
sincronizar_1(spectime *argp, CLIENT *clnt)
{
	static struct respuesta clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, sincronizar,
		(xdrproc_t) xdr_spectime, (caddr_t) argp,
		(xdrproc_t) xdr_respuesta, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}