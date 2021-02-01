#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;
  pid = fork();

  if (pid == -1){
    return -1;
  }
  if (pid == 0){
    ppid = getppid();
    printf("Child-process, pid = %d, ppid = %d\n", (int)pid, (int)ppid);
  }
  else {
    ppid = getppid();
    printf("Parent-process, pid = %d, ppid = %d\n", (int)pid, (int)ppid);
  }
  return 0;
}
