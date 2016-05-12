#include "../mymsg.h"

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
