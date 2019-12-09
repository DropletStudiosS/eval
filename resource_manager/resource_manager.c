#define _GNU_SOURCE
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/resource.h>

int main(int argc, char* argv[]){

	//cpu limits
	struct rlimit cpuold, cpunew;
	struct rlimit *cpunewp;
	//data segment limits
	struct rlimit segold, segnew;
	struct rlimit *segnewp;
	//memlock limits
	struct rlimit memold, memnew;
	struct rlimit *memnewp;

	if(!(argc < 6))
		exit(EXIT_FAILURE);

	char *fname = strdup(argv[1]);

	pid_t pid = fork();
	
	if(pid == 0)
	{
		execv("/bin/bash", fname);
		exit(127);
	}
	else
		waitpid(pid, 0, 0);

	cpunewp = NULL;
	segnewp = NULL;
	memnewp = NULL;
	if(argc == 7){
		
		cpunew.rlim_cur = atoi(argv[2]);
		cpunew.rlim_max = atoi(argv[3]);
		cpunewp = &cpunew;
		
		segnew.rlim_cur = atoi(argv[4]);
		segnew.rlim_max = atoi(argv[5]);
		segnewp = &segnew;

		memnew.rlim_cur = atoi(argv[6]);
		memnew.rlim_max = atoi(argv[7]);
		memnewp = &memnew;
	}

	/*set cpu time limit of target process*/	/*prlimit (__pid_t pid, enum __rlimit_resource resource,
         										const struct rlimit *new_rlimit, struct rlimit *old_rlimit)*/
	prlimit(pid, RLIMIT_CPU, cpunewp, &cpuold);
	prlimit(pid, RLIMIT_DATA, segnewp, &segold);
	prlimit(pid, RLIMIT_MEMLOCK, memnewp, &memold);

	exit(EXIT_SUCCESS);

	return 0;
}
