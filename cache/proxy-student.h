/*
 *  This file is for use by students to define anything they wish.  It is used by the proxy cache implementation
 */
 #ifndef __CACHE_STUDENT_H__
 #define __CACHE_STUDENT_H__
 
 #endif // __CACHE_STUDENT_H__

#include <pthread.h>
#include "steque.h"
#include "gfserver.h"

typedef struct thread_pool {
	int threadnum;
	int workthreadnum;
	pthread_t* taskque;
	steque_t* taskque;
	int tasknum;
	pthread_mutex_t* lock;
	pthread_cond_t* cond;
} thread_pool;

typedef struct request_context {
	gfcontext_t* ctx;
	char* path;
} request_context;