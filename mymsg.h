#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
//Basic Include
#include <sys/msg.h>
//Message Buffer Include
#include <string.h>
//String Include
#include <sys/sem.h>
//Named Semaphore Include
#include <sys/ipc.h>
#include <sys/stat.h>
#include <errno.h>
//Other Include
//----------
#define MSG_FILE "CenterSrv.c"
#define BUFFER 255
#define PERM S_IRUSR|S_IWUSR
//Define
//----------
typedef struct msgbuf{ 		/* 消息定义的参照格式 */
  long mtype;       						/* 消息类型（大于0的长整数）  */
	char mtext[BUFFER+1]; 		/*消息正文*/
}msgbuf;
//Message Buffer Struct
typedef struct msqid_ds msgque;
//Message Queue Struct
typedef struct USER_TABLE{ 
  char name[20];				//用户名
  int pid;								//由 CenterSrv 分配的ID
  int sendsrvid;				//Clinet使用的 Sendsrv ID
}users;
//User Table Struct
