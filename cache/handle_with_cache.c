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

#define BUFSIZE (8803)

//Replace with an implementation of handle_with_cache and any other
//functions you may need.

void shared_memory_init(size_t)
{

}
void shared_memory_clean()
{

}
void message_socket_init()
{

}
void message_socket_clean()
{

}
ssize_t handle_with_cache(gfcontext_t *ctx, char *path, void* arg){
	/* 1. create a request structure 
	   2. pass request to simple_cache(through message queue?)
	   3. receive message
	*/
	
}

