//In case you want to implement the shared memory IPC as a library...
#include "shm_channel.h"
#define BUFSIZE (8803)
int counter = 0;
int shared_memory_init()
{
	key_t key;
	int shm_id = 0;
	if ((key = ftok("handle_with_cache.c",counter)) == -1) {
		fprintf(stderr, "shared_memory creation error\n");
		exit(1);
	}
	shm_id = shmget(key, BUFSIZE, 0666 | IPC_CREAT);
	counter++;
	return shm_id;
}

shared_data* shared_memory_attach(int shm_id)
{
	shared_data* shm_empty = shmat(shmid, (void *)0, 0);
	if (shm_empty == (shared_data*)(-1))
	{
		fprintf(stderr, "attach to shared_memory error\n");
		exit(1);
	}
	return shm_empty;
}

void init_shm_content(shared_data* shm)
{
	bzero(shm->data, BUFSIZE);
	shm->semaphore=sem_init(&semaphore ,1 ,1);
	shm->data_status = EMPTY;
}

void shared_memory_detach(void * addr)
{
	shmdt(addr);
}