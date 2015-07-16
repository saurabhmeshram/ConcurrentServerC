#ifndef __COMMON_HEAD_H_
#define __COMMON_HEAD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Common Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

/* Socket related files */
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* Misc Macros */

#define SIZE64 64

#define _LINE 	__LINE__
#define _FILE	__FILE__
#define _FUNC 	__func__
#define ENTER 	printf("Entered Function [%s][%d]\n", _FUNC, _LINE)
#define EXIT  	printf("Exiting Function [%s][%d]\n", _FUNC, _LINE)
#define DEBUG  	printf("Here in [%s][%d]\n", _FUNC, _LINE)

#define TRUE 	1
#define FALSE 	0

#ifdef __cplusplus
}
#endif
#endif 		/* For __COMMON_HEAD_H_*/
