#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	pid_t pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("Curr. Pid = %d, curr. Ppid = %d\n", (int)pid, (int)ppid);
	// Pid goes +1 every new ex. because linux reserves thread.
	return 0;
}
