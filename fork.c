//Zombie Process

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
 int status ;
 pid_t pid;
 pid=fork();
 if(pid!=0)
 {
   sleep(2);
   system("ps");
   wait(&status);
   system("ps");
   printf("\nParent Process");
   printf("\nID = %d ",getpid());
   printf("\nParent ID = %d ",getppid());
   printf("\nChild ID = %d ",pid);
 }
 else
 {
  printf("\nChild Process");
  printf("\nChild ID = %d ",getpid());
  printf("\nParent ID = %d ",getppid());
 }
 return 0;
} 

//Orphan Process
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
 int status ;
 pid_t pid;
 pid=fork();
 if(pid!=0)
 {
   printf("\nParent Process");
   printf("\nID = %d ",getpid());
   printf("\nParent ID = %d ",getppid());
   printf("\nChild ID = %d ",pid);
 }
 else
 {
  sleep(2);
  printf("\nChild Process");
  printf("\nChild ID = %d ",getpid());
  printf("\nParent ID = %d ",getppid());
 }
 return 0;
} 



