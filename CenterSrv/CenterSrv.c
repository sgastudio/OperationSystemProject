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
//----------
key_t msgkey=0;
msgbuf msg;
int msgid;
//Goble Var
int init()
{
    if((msgkey=ftok(MSG_FILE,66))==-1)
    {
        fprintf(stderr,"Creat Key Error：%s \n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Create Key Complete.\n");
    if((msgid=msgget(msgkey,PERM|IPC_CREAT))==-1)
    {
        fprintf(stderr,"Creat MessageQueue Error：%s \n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Create Message Queue Complete.\n");
    //Message Queue Create
    msg.mtype=1;
	return 0;
}

int uninit()
{
	if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "Remove MessageQueue Error%s \n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int process()
{
	while(1)
	{
		msgrcv(msgid,&msg,sizeof(struct msgbuf),1,0);
	}
	return 0;
}

int client_pidsend()
{
	return 0;
}

int main()
{
	printf("Init...\n");
	init();
	printf("Init Complete.\n");
	return 0;
}
