/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "SumaArreglos.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

nametype *
cadena_1(nametype *argp, CLIENT *clnt)
{
	static nametype clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, cadena,
		(xdrproc_t) xdr_nametype, (caddr_t) argp,
		(xdrproc_t) xdr_nametype, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}