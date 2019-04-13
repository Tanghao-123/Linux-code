#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>

#define FIFONAME "mypipe"


int main()
{
  int fd = open(FIFONAME,O_WRONLY);
  if(fd < 0)
  {
    perror("open error\n");
    return -1;
  }
  char buf[1024];
  while(1)
  {
    printf("please enter message to server#");
    fflush(stdout);
    ssize_t s = read(0,buf,sizeof(buf)-1);
    buf[s] = 0;
    write(fd,buf,strlen(buf));
  }
  close(fd);

  return 0;
}
