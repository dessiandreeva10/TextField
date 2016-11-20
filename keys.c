#ifndef KEYS_H_
#define KEYS_H_

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "field.h"
#include "functions.c"
#include "printing.c"

/**************************************************
/* Function name: Begin()
/* Author: desia
/* Params: it's waits to press something and invoke
 * 		   the function for this key;
/* Functionality:
***************************************************/

int Begin(EnteredText_t *pEnteredKeys) 
{
   pEnteredKeys = GlobalGet();
   char command = '\0';
   char ident = '\0';
   
   
   while(1)
   {
	   command = getchar();
	   
	   if(command == ESC)
	   {
			getchar();
			ident = getchar();
	   }
	   
	   if(command == TAB)
	   {
		return EXIT_SUCCESSFULL;
	   }
	   
	   switch(command)
	   {
		case ESC:
			ArrowsMovingKeys(ident, pEnteredKeys);
			break;
		case SPACE:
			SpaceKeyPressed(pEnteredKeys);
			break;
		case BACKSPACE:
			BackpaceKeyPressed(pEnteredKeys);
			break; 
		default:
			EnteredText(command, pEnteredKeys);
			break;
		   
		}
	}
	
	return INIT_OK;
}

/**************************************************
/* Function name: ArrowsMovingKeys()
/* Author: desia
/* Params: char ident - last byte that identifies
						the pressed arrow key;
/* Functionality:
***************************************************/

void ArrowsMovingKeys(char ident, EnteredText_t *pEnteredKeys)
{
	pEnteredKeys = GlobalGet();
	
	switch(ident)
	{
	case 'A':
	break;
	case 'B':
	break;
	case 'C':
	RightKeyPressed(pEnteredKeys);
	break;
	case 'D':
	LeftKeyPressed(pEnteredKeys);
	break;
	case 'H':
	HomeKeyPressed(pEnteredKeys);
	break;
	case 'F':
	EndKeyPressed(pEnteredKeys);
	break;
	case 51:
	getchar();		 
	DeleteKeyPressed(pEnteredKeys);
	break;
	}
}


/********************************************************
/* Function name: EnteredText()
/* Author: desia
/* Params: retChar 
/* Functionality: fills the char array
/* Params: retChar - the entered character in Begin()
**********************************************************/
	
void EnteredText(char retChar, EnteredText_t *pEnteredKeys) 
{	
	pEnteredKeys = GlobalGet();
	
	if(pEnteredKeys->cursor > 0)
	{	
		EnterCharInSomePosition(retChar,0, pEnteredKeys);
		retChar = '\0';	
	}
	else
	{
		//CleanBuffer(pEnteredKeys);
		pEnteredKeys->text[pEnteredKeys->tcur] = retChar;
		pEnteredKeys->text[pEnteredKeys->tcur+1] = '\0';
		pEnteredKeys->tcur++;
		pEnteredKeys->endT++;
		if(pEnteredKeys->endT > 17)
		pEnteredKeys->begin++;
		
		
		if(pEnteredKeys->cursorVisible < 18)
		{
			pEnteredKeys->cursorVisible++;
		}
	
		PrintResult(pEnteredKeys->begin,pEnteredKeys->endT, pEnteredKeys);
	
	}	
}

/*********************************************
/* Fucntion name: LeftKeyPressed()
/* Author: desia
/* Params: 
/* Functionality: Checks the pointers values  
		and prints the text inside the filed;
***********************************************/

void LeftKeyPressed(EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	
	if(pEnteredKeys->cursorVisible > 2)
	{
		pEnteredKeys->cursorVisible--;
		if(pEnteredKeys->cursor < pEnteredKeys->tcur)
		pEnteredKeys->cursor++;
		MOVELEFT();
	}
	
	if(pEnteredKeys->cursorVisible == 2)
	{
		
		if(pEnteredKeys->begin > 0 && pEnteredKeys->endT > 0)
		{
			if(pEnteredKeys->cursor <= pEnteredKeys->tcur)
			pEnteredKeys->cursor++;
			pEnteredKeys->begin--;
			
			if(pEnteredKeys->endT > pEnteredKeys->begin + 17)
			pEnteredKeys->endT--;
			else
			pEnteredKeys->endT = pEnteredKeys->begin + 17;
		}
	}

	PrintResult(pEnteredKeys->begin,pEnteredKeys->endT, pEnteredKeys);	

}	

/***********************************************
/* Fuction name: RightKeyPressed();
/* Author: desia
/* Params: 
/* Functionality: Check the pointers (counters)
 * 				   values and prints text inside 
 * 					the field;
************************************************/

void RightKeyPressed(EnteredText_t *pEnteredKeys) 
{	
	pEnteredKeys = GlobalGet();
	
	if(pEnteredKeys->cursorVisible < 18 && pEnteredKeys->cursor > 0)
	{
		MOVERIGHT();
		pEnteredKeys->cursorVisible++;
		if(pEnteredKeys->cursor > 0)
		pEnteredKeys->cursor--;			
	}
	
	
	if(pEnteredKeys->cursorVisible == 18)
	{
		if(pEnteredKeys->endT <= pEnteredKeys->tcur)
		{
			if(pEnteredKeys->cursor > 0)
			pEnteredKeys->cursor--;
		}
		
		if(pEnteredKeys->endT < pEnteredKeys->tcur)
		{
			pEnteredKeys->begin++;
			pEnteredKeys->endT++;
		}
	}
	
	PrintResult(pEnteredKeys->begin,pEnteredKeys->endT, pEnteredKeys);
}


/*******************************************
/* Function name: DeleteKeyPressed() 
/* Author: desia
/* Params: 
/* Functionality: deletes a char befind
 * 					the cursor; 
********************************************/

void DeleteKeyPressed(EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int findPos = 0;
	
	if(pEnteredKeys->cursor > 0)
	{
		findPos = pEnteredKeys->tcur - pEnteredKeys->cursor;
				
		RemoveChar(findPos, pEnteredKeys);
		PrintMessage();
		PrintAfterDelete(findPos, pEnteredKeys);
		
	}
}

/*******************************************
/* Function name: BackpaceKeyPressed() 
/* Author: desia
/* Params: 
/* Functionality: delete a char infront 
 * 					of the cursor
********************************************/

void BackpaceKeyPressed(EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int findPos = 0;
	
	if(pEnteredKeys->cursor <= pEnteredKeys->tcur)
	{
		findPos = pEnteredKeys->tcur - pEnteredKeys->cursor;
		
		if(pEnteredKeys->cursor != pEnteredKeys->tcur && pEnteredKeys->cursor > 0)
		{
			findPos = findPos - 1;
		}
		
		if(pEnteredKeys->tcur > pEnteredKeys->cursor) /* Either way it will remove characters that it shouldn't*/
		{
			RemoveChar(findPos, pEnteredKeys);
			PrintMessage();
			PrintAfterBS(findPos, pEnteredKeys);
		}
	}
}

/***************************************************
/* Function name: SpaceKeyPressed() 
/* Author: desia
/* Params: 
/* Functionality: insert space and print the result 
****************************************************/

void SpaceKeyPressed(EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int findPos = 0;
	
	if(pEnteredKeys->cursor >= 0)
	{
		findPos = pEnteredKeys->tcur - pEnteredKeys->cursor;
		CheckWhereToAddSpace(findPos, pEnteredKeys);
		PrintAfterAdded(pEnteredKeys);
	}
}

					
/********************************************************
/* Function name: HomeKeyPressed()
/* Parames: none
/* Functionality: Gives the counting pointers their
 * 				  initial values and prints the begginig 
 * 				  of the text inside the field;
*********************************************************/

void HomeKeyPressed(EnteredText_t *pEnteredKeys) 
{	
	pEnteredKeys = GlobalGet();
	
	pEnteredKeys->begin = 0;
	CleanBuffer(pEnteredKeys);
	if(pEnteredKeys->tcur >= 17)
	{
		pEnteredKeys->endT = pEnteredKeys->begin + 17;
	}
	else
	{
		pEnteredKeys->endT = pEnteredKeys->tcur ;
	}
	pEnteredKeys->cursorVisible = 2;
	pEnteredKeys->cursor = pEnteredKeys->tcur;
		
	PrintResult(0,17, pEnteredKeys);
	GOTOXY(3,2);
}


/*******************************************
/* Function name: EndKeyPressed() 
/* Params:
/* Functionality: Prints the end of the array
/* inside the field; Gives the pointers max
/* values;
********************************************/

void EndKeyPressed(EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	
	CleanBuffer(pEnteredKeys);
	if(pEnteredKeys->tcur < 17)
	{
		pEnteredKeys->cursorVisible = pEnteredKeys->tcur + 2;
		pEnteredKeys->begin = 0;
	}
	else
	{	
		pEnteredKeys->begin = pEnteredKeys->tcur - 17;
		pEnteredKeys->cursorVisible = 18;
	}
	
	pEnteredKeys->cursor = 0;
	pEnteredKeys->endT = pEnteredKeys->tcur;
	
	PrintResult(pEnteredKeys->begin, pEnteredKeys->endT, pEnteredKeys);
		
}


/***************************************************
/* Function name: AddCharInSomePosition() 
/* Author: desia
/* Params: the new char that should be added 
/* Functionality: enter charachter when the cursor
 *				is not at the end of the text;
****************************************************/

void EnterCharInSomePosition(char newchar, int position, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int findPos = 0;
	
	findPos = pEnteredKeys->tcur - pEnteredKeys->cursor;
	AddChar(findPos,newchar, pEnteredKeys);
	pEnteredKeys->text[pEnteredKeys->tcur + 1] = '\0';
	
	PrintAfterAdded(pEnteredKeys);						
}

#endif
