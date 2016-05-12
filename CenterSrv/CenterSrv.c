#include "../mymsg.h"
//----------
//key_t msg_key=0;		//系统生成得消息队列key
msgbuf msg_global;		//全局消息
int msg_id;			//消息队列ID
users* USERLIST;		//用户链表
long user_num=0;		//用户数量（ID）
long sendsrv_num=0;
long rcvsrv_num=0;
//Goble Var
//---------
//Pre Define Program Blocks

int msgqueue_init(char *message_file, int* msgid)
{
	key_t msgkey;
	 if((msgkey=ftok(message_file, 66))==-1)
    {
        fprintf(stderr, "Creat Key Error：%s \n", strerror(errno));
        return -1;
    }
    printf("Create Key Complete.\n");
    if((*msgid=msgget(msgkey, PERM|IPC_CREAT))==-1)
    {
        fprintf(stderr,"Creat Message Queue Error：%s \n", strerror(errno));
        return -1;
    }
    printf("Create Message Queue Complete.\n");
    //Message Queue Create
    return 0;
}

int  msgqueue_uninit(int msgid)
{
	if(msgctl(msgid,  IPC_RMID,  0) == -1)
    {
        fprintf(stderr,  "Remove Message Queue Error%s \n", strerror(errno));
        return -1;
    }
    printf("Remove Message Queue Complete.\n");
    return 0;
}

int msgqueue_send(int msgid, int msgtype, char* megtext)
{
	msgbuf msg;
	msg.mtype=msgtype;
	strncpy(msg.mtext,megtext,BUFFER);
	if(msgsnd(msgid, &msg, sizeof(msgbuf), 0)!=0)
	{
		 return -1;
	}
	return 0;
}

int process()
{
	while(1)
	{
		
	}
	return 0;
}

int client_init()
{
	int temp_msgid;
	msgbuf msg_clinet_init;
	char temp_text[BUFFER+1];
	char temp_name[20];
	char temp_location[4096];
	users* templist;
	//var
	while(1)
	{
		msgrcv(msg_id, &msg_clinet_init, sizeof(msgbuf), 1, 0);
		sscanf(msg_clinet_init.mtext, "%s %s", temp_name, temp_location);
		//Message Read Complete
		if(sendsrv_num<=0)
		{
			printf("There is no Send Server.\n");
			break;
		}
		if(user_num/PERSON_PER_SERVER>sendsrv_num)
		{
			printf("There is no Free Send Server to attach.\n");
			break;
		}
		
		templist=USERLIST;
		USERLIST=malloc(sizeof(users));
		USERLIST->next=templist;
		strcpy(USERLIST->name,temp_name);
		strcpy(USERLIST->location,temp_location);
		user_num++;
		USERLIST->pid=user_num;
		USERLIST->sendsrvid=sendsrv_num;
		
		if(msgqueue_init(USERLIST->location, &temp_msgid)==-1)
		{
			printf("Init Message Queue Failed\n");
			break;
		}
		sscanf(temp_text,"ID|%d",&USERLIST->pid);
		msgqueue_send(temp_msgid,4,"ID ");
		if(msgqueue_uninit(temp_msgid)==-1)
		{
			printf("Uninit Message Queue Failed\n");
			break;
		}
	}
	return 0;
}

int init()
{
   if(msgqueue_init(MSG_FILE, &msg_id)==-1)
   {
		exit(EXIT_FAILURE);
	}
	
	return 0;
}

int main()
{
	printf("Init...\n");
	init();
	printf("Init Complete.\n");
	return 0;
}
