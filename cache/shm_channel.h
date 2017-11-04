//In case you want to implement the shared memory IPC as a library...
#include <pthread.h>
#define BUFSIZE (8803)
typedef enum shared_status {
	WRITE_FINISH,
	READ_FINISHI,
	AVAILABLE,
	EMPTY
} shared_status;

typedef struct shared_data {
	char* data;
	ssize_t filesize;
    sem_t semaphore;
	shared_status data_status;
} shared_data;

int shared_memory_init(int& shm_id);
shared_data* shared_memory_attach(int shm_id);
void init_shm_content(shared_data* shm);
void shared_memory_detach(void * addr);