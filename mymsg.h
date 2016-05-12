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
#define PERSON_PER_SERVER 5
//Define
//----------
typedef struct MSG_BUF{ 		//消息定义的参照格式
  	long mtype;       		// 消息类型（大于0的长整数）  1注册请求 2注销请求 3其他指令 4消息
	char mtext[BUFFER+1]; 		//消息正文
}msgbuf;
//Message Buffer Struct
typedef struct msqid_ds msgque;
//Message Queue Struct
typedef struct USER_TABLE{ 
	int pid;			//由 CenterSrv 分配的ID
  	char name[20];			//用户名
  	int sendsrvid;			//Clinet使用的 Sendsrv ID
  	char location[4096];		//消息队列文件地址
  	struct USER_TABLE * next;	//下一记录地址
}users;
//User Table Struct
