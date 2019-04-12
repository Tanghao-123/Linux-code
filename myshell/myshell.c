#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define MAX 1024
#define NUM 16


int main()
{
  char* myargv[NUM];
  char cmd[MAX]; 
  printf("[tanghao@localhost myshell]# ");
  fgets(cmd,strlen(cmd),stdin);
  cmd[strlen(cmd)-1] = '\0';

  int i = 0;
  myargv[i++] = strtok(cmd," ");
  char* ret = NULL;
  while(ret = strtok(NULL," "))
  {
    myargv[i++] = ret;
  }
  myargv[i] = NULL;
  pid_t pid = fork();
  if(pid < 0)
  {
    perror("fork");
    exit(-1);
  }
  else if(pid == 0)
  {
    execvp(myargv[0],myargv);
    exit(1);
  }
  else
  {
    waitpid(-1,NULL,0);
  }

}

