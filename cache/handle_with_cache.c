#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <sys/signal.h>
#include <printf.h>
#include <curl/curl.h>

#include "gfserver.h"
#include "proxy-student.h"
#include "shm_channel.h"
#define BUFSIZE (8803)
#define RECONNECTTIME (5)
//Replace with an implementation of handle_with_cache and any other
//functions you may need.

int shm_id;
int requestshmid;
int responseshmid;
void create_message_queue() {
	printf("create message queue \n");
	key_t requestkey;
	if ((requestkey = ftok("handler_with_cache.c", 'R')) == -1) {
		fprintf(stderr, "request queue creation error\n");
		exit(1);
	}
	if ((requestshmid = msgget(requestkey, 0666 | IPC_CREAT)) == -1) {
		fprintf(stderr, "request queue creation error\n");
		exit(1);
	}
	key_t responsekey;
	if ((responsekey = ftok("handler_with_cache.c", 'D')) == -1) {
		fprintf(stderr, "response queue creation error\n");
		exit(1);
	}
	if ((responseshmid = msgget(responsekey, 0666 | IPC_CREAT)) == -1) {
		fprintf(stderr, "response queue creation error\n");
		exit(1);
	}
}
cache_status wait4request(cache_request* request)
{
	int connecttime = 0;
	while ((connecttime < RECONNECTTIME) && (msgrcv(responseshmid, request, sizeof(cache_request), request->mtype, 0)) < 0)
	{
		sleep(1);
		connecttime++;
	}
	if (connection >= RECONNECTTIME)
	{
		printf("exceed connection time\n");
		return FILE_REQUESTING;
	}
	return request->status;
}
pthread_mutex_t lock;
pthread_mutex_init(lock);
ssize_t handle_with_cache(gfcontext_t *ctx, char *path, void* arg){
	/* 1. create a request structure 
	   2. pass request to simple_cache(through message queue?)
	   3. receive message
	*/
	/* Don't know whether these two arg should be combined as handler_with_curl.c
	char buffer[BUFSIZE];
	char *data_dir = arg;
	strcpy(buffer,data_dir);
	strcat(buffer,path);
	*/
	cache_request* request = malloc(sizeof(cache_request));
	request->mtype = 1;
	request->filedp = 0;
	reques->filesize = 0;
	request->shmid = shared_memory_init();
	strcpy(request->path, buffer);
	request->status = FILE_REQUESTING;
	int sendlen = sizeof(cache_request) - sizeof(long);
	// send request
	if ((msgsnd(requestshmid, request, sendlen, 0)) < 0)
		fprintf(stderr, "send message error\n");
	// receive from message queue
	cache_status request_outcome = wait4request(request);
	if (cache_status != FILE_IN_CACHE)
	{
		printf("Cannot find file in cache\n");
		gfs_sendheader(ctx, GF_FILE_NOT_FOUND, 0);
	} else {
		// file in cache, receive data from shared_memory
		printf("File found in cache, begin download\n");
		shared_data* transfer_data = malloc(sizeof(shared_data));
		transfer_data = shared_memory_attach(request->shmid);
		gfs_sendheader(ctx, GF_OK, transfer_data->filesize);
		if (transfer_data != NULL)
		{
			// successful transfer
			int bytes_transfered = 0;
			sem_wait(&transfer_data->semaphore);
			while(bytes_transfered < request->filesize)
			{
				if (transfer_data->status == AVAILABLE)
				{
					pthread_mutex_lock(lock);
					size_t send_bytes = gfs_send(ctx, (void *)(transfer->data), BUFSIZE);
					bytes_transfered += send_bytes;
					pthread_mutex_unlock(lock);
				} else if (transfer_data->status == WRITE_FINISH)
				{
					pthread_mutex_lock(lock);
					size_t send_bytes = gfs_send(ctx, (void *)(transfer->data), request->filesize - bytes_transfered)
					bytes_transfered += send_bytes;
					pthread_mutex_unlock(lock);
				}
			}
			sem_post(&transfer_data->semaphore);
		}
	}
	shared_memory_detach(transfer_data)；
	free(request);
}

