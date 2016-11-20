#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "functions.c"
#include "keys.c"
#include "printing.c"

int main()
{
	static struct termios oldt, newt;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&newt);

	pEnteredKeys = InitGlobalStruct(&pEnteredKeys); 
	
	if(NULL != pEnteredKeys)
	{
		PrintMessage();
		if(EXIT_SUCCESSFULL == Begin(pEnteredKeys))
		{
			CLEAR();
			printf("Exit successfull!");
			tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
		}	
	} 
	else
	{
		printf("Something went wrong! Memory allocation error!");
	}
	
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
	return 0;
}
