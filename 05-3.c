#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fdP[2], result;
  int     fdC[2];
  size_t size;
  char  resstring[14];

  if (pipe(fdP) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }
  if (pipe(fdC) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {

   /* Parent process */

    if (close(fdP[0]) < 0) {
      printf("parent: Can\'t close reading side of parent to child pipe\n");
      exit(-1);
    }
    if (close(fdC[1]) < 0) {
      printf("parent: Can\'t close writing side of child to parent pipe\n");
      exit(-1);
    }

    size = write(fdP[1], "Hello, world!", 14);

    if (size != 14) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }

    if (close(fdP[1]) < 0) {
      printf("parent: Can\'t close writing side of parent to child pipe\n");
      exit(-1);
    }
    if (close(fdC[0]) < 0) {
      printf("parent: Can\'t close reading side of child to parent pipe\n");
      exit(-1);
    }

    printf("Parent exit\n");

  } else {

    /* Child process */

    if (close(fdP[1]) < 0) {
      printf("child: Can\'t close writing side of parent to child pipe\n");
      exit(-1);
    }
    if (close(fdC[0]) < 0) {
      printf("child: Can\'t close reading side of child to parent pipe\n");
      exit(-1);
    }

    size = read(fdP[0], resstring, 14);

    if (size < 0) {
      printf("Can\'t read string from pipe\n");
      exit(-1);
    }

    printf("Child exit, resstring:%s\n", resstring);

    if (close(fdP[0]) < 0) {
      printf("child: Can\'t close reading side of parent to child pipe\n");
      exit(-1);
    }
    if (close(fdC[1]) < 0) {
      printf("child: Can\'t close writing side of child to parent pipe\n");
      exit(-1);
    }
  }

  return 0;
}
