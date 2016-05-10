#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
//Basic Include
#include <sys/msg.h>
//Message Buffer Include
#include <string.h>
//String Include
char NAME[21]={'\0'};
//Goble Var
int  Init()
{
	do
	{
		printf("Please Enter Your Nick Name(20 Letter Limit)\n");
		scanf("%s", NAME);
	}while(NAME[1]=='\0');
	return 0;
}

int main()
{
	init();
	return 0;
}
