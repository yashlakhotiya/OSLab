#define TEXT_SZ 2048

struct shared_use_St{
	int written_by_you;
	char some_text[TEXT_SZ];
};

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>