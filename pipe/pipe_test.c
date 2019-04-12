#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
  int fds[2];
  if(pipe(fds) < 0)
  {
    perror("pipe error");
    exit(-1);
  }

  pid_t id = fork();
  if(id < 0)
  {
    perror("fork error");
    exit(-2);
  }
  else if(id == 0)
  {
    close(fds[0]);
    const char* message = "I am child, I am sending a message";
    int i = 5;
    while(i--)
    {
      write(fds[1],message,strlen(message));
      sleep(1);
    }
    printf("child write done...\n");
    close(fds[1]);
    exit(1);
  }
  else
  {
    close(fds[1]);

    char buf[1024];
    while(1)
    {
      ssize_t s = read(fds[0],buf,sizeof(buf)-1);
      if(s > 0)
      {
        buf[s] = 0;
        printf("I am father,I am receiving message :\n");
        printf("%s\n",buf);
        printf("father recv done...\n");
      }
      else if(s == 0)
      {
        printf("child quit done, father quit too\n");
        break;
      }
      else 
      {
        perror("read message error ");
      }
    }
    close(fds[0]);
  }
  pid_t ret = waitpid(id,NULL,0);
  if(ret > 0)
    printf("wait child success\n");
}
