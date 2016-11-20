#ifndef PRINT_H_
#define PRINT_H_


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "field.h"
#include "functions.c"


void PrintField() 
{
	printf(
	"\n"
    "╔═════════════════╗\n"
    "║                 ║\n"
    "╚═════════════════╝\n"
	);
	
}


/********************************************
/* Function name: PrintResult() 
/* Author: desia
/* Params: begin and end of text that 
/* will be printed
/* Functionality: prints portion of the text
**********************************************/

void PrintResult(int begin, int end, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int i = 0;

	GOTOXY(3,2);
		
	for(i = begin; i < end; i++)
	{
		printf("%c",pEnteredKeys->text[i]);
	}				
	GOTOXY(3,pEnteredKeys->cursorVisible);
}


/**************************************************
/* Function name: PrintAfterBS() 
/* Author: desia
/* Params: the position where char should 
/* be deleted
/* Functionality: prints the text after backspace
 * 				  key is pressed
***************************************************/
void PrintAfterBS(int findPos, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	
	if(pEnteredKeys->tcur > 0)
	{
		pEnteredKeys->tcur--;
		if(pEnteredKeys->endT > 0)
		pEnteredKeys->endT--;
		if(pEnteredKeys->endT == 0)
		pEnteredKeys->begin = 0;
	}
	
	if(pEnteredKeys->tcur <= 17 || pEnteredKeys->endT <= 17)
	{
	  if(pEnteredKeys->cursorVisible > 2)
		pEnteredKeys->cursorVisible--;	
			
	}
	
	if(pEnteredKeys->tcur > 17 && pEnteredKeys->begin > 0)
	{
		pEnteredKeys->begin--;
	}
	
	PrintResult(pEnteredKeys->begin,pEnteredKeys->endT, pEnteredKeys);
}

	
/***********************************************
/* Function name: PrintAfterAdded() 
/* Author: desia
/* Params: none
/* Functionality: prints the result after
 * 				  entering a nwe char or space
************************************************/

void PrintAfterAdded(EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	
	pEnteredKeys->tcur++;
	if(pEnteredKeys->cursorVisible < 18)
	{
		pEnteredKeys->cursorVisible++;
		if(pEnteredKeys->endT < 17)
			pEnteredKeys->endT++;
	
	}
	else
	{ 
		if(pEnteredKeys->endT >= 17)
		pEnteredKeys->begin++;
		pEnteredKeys->endT++;
		
	}	
	
	PrintResult(pEnteredKeys->begin,pEnteredKeys->endT, pEnteredKeys);
}

/*******************************************
* Function name: PrintAfterDelete() 
* Author: desia
* Params: 
* Functionality: print the text after delete
* 			     key pressed
********************************************/

void PrintAfterDelete(int findPos, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	
	
	if(pEnteredKeys->tcur > 0) 
		pEnteredKeys->tcur--;
		
	if(pEnteredKeys->cursor > 0)
	{
		pEnteredKeys->cursor--;
	}
	else
	{
		pEnteredKeys->cursor = 0;

	}
	
	if(pEnteredKeys->endT > 0) 
	pEnteredKeys->endT--;
		
	PrintResult(pEnteredKeys->begin,pEnteredKeys->endT, pEnteredKeys);
}

/**************************************************
/* Function name: PrintMessage()
/* Author: desia
/* Params: none
/* Functionality: Prints the field and the message
				  for exit; Used in Begin(), 
				  DeleteKeyPressed(),
				  BackspaceKeyPressed();
***************************************************/

void PrintMessage()
{
	CLEAR();
	PrintField();
	GOTOXY(5,2);
	printf("Enter TAB key for exit!");
	GOTOXY(3,2);
}

#endif
