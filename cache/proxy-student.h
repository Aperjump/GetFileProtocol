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
	pthread_t* thread;
	steque_t* taskque;
	int tasknum;
	pthread_mutex_t* lock;
	pthread_cond_t* cond;
} thread_pool;

typedef enum cache_status {
	FILE_REQUESTING,
	FILE_NOT_FOUND,
	FILE_IN_CACHE
} cache_status;

typedef struct cache_request {
	long mtype;
	char* path[512];
	ssize_t filesize;
	cache_status status;
	int shmid;
} cache_request;