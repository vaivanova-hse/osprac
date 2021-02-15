#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  size_t  size;
  char    string[] = "Hello, world!";
  int     readErr;
  // 14 for that case.
  char    readBuf[14];
  (void)umask(0);

  if ((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = write(fd, string, 14);

  if (size != 14) {
    printf("Can\'t write all string\n");
    exit(-1);
  }

  if ((fd = open("myfile", O_RDONLY, 0666)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  readErr = read(fd, readBuf, sizeof(readBuf));

  if (readErr < 0) {
    printf("Can\'t read file\n");
    exit(-1);
  }

  printf(readBuf);
  printf("\n");

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }

  return 0;
}
