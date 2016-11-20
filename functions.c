#ifndef FUNC_H_
#define FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "field.h"

EnteredText_t *GlobalGet() 
{
	return pEnteredKeys;
}

void CleanBuffer(EnteredText_t *pEnteredKeys)
{
	
	pEnteredKeys = GlobalGet();
	
	if(pEnteredKeys->tcur == 0)
		bzero(pEnteredKeys->text, BUFFER_MAXSIZE);
		
}
/*******************************************************************
/* Function name: InitGlobalStruct()
/* Author: desia
/* Params: double pointer to the global struct
/* Variables: Struct with fields:
 
	  cursor => points which index in the array is reached;
	  begin => points to array's index where 
			   the printed text starts;
	  tcur => counts the number of entered chars; 
	  cursorVisible => the cursor which we see 
						when we move around the field;
	  endT => points to array's index where the printed text ends;
	   
/* Functionality: Init function for the global struct
********************************************************************/

EnteredText_t *InitGlobalStruct(EnteredText_t **ppEnteredKeys) 
{
	EnteredText_t *pEnteredKeys = (EnteredText_t*)malloc(sizeof(EnteredText_t*));
	bzero(pEnteredKeys->text, BUFFER_MAXSIZE);
	pEnteredKeys->cursor = 0;
	pEnteredKeys->begin = 0;
	pEnteredKeys->tcur = 0;
	pEnteredKeys->cursorVisible = 2;
	pEnteredKeys->endT = 0;
		
	*ppEnteredKeys = pEnteredKeys;
	
	return pEnteredKeys; 
}

/*************************************************, 
/* Function name: CheckWhereToAddSpace()
/* Author: desia
/* Params: findPos - index in the array, where 
 * 						to add space
/* Functionality: Checks if the space is added
/* in the edn of the text or in another place 
*************************************************/

void CheckWhereToAddSpace(int findPos, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();	
	
	if(findPos == pEnteredKeys->tcur)
	{
		pEnteredKeys->text[findPos] = ' ';
		pEnteredKeys->text[findPos + 1] = '\0';
		pEnteredKeys->cursor = 0;
	}
	else
	{
		AddSpace(findPos, pEnteredKeys);		
	}
	
}


/*******************************************
/* Function name: RemoveChar() 
/* Author: desia
/* Params: the index in array 
/* Functionality: deletes a character from 
/*	given position;
********************************************/

void RemoveChar(int findPos, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int i = 0;
	int j = 0;
	
	for(i = 0; i < pEnteredKeys->tcur; i++)
	{	
		if(i == findPos)
		{
			for(j = i; j < pEnteredKeys->tcur; j++)
			{
				pEnteredKeys->text[j] = pEnteredKeys->text[j+1];
				
			}
			
			pEnteredKeys->text[j] = '\0';	
		}
	}
		
}


/**************************************************
/* Function name: AddSpace() 
/* Author: desia
/* Params: the position where space was entered
/* Functionality: insert a space in an array
 * 				   from given index (findPos); 
****************************************************/

void AddSpace(int findPos, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	int i = 0;
	int j = 0;
	char helpMas[256];
	
	bzero(helpMas,BUFFER_MAXSIZE);
	
	for(i = 0; i < pEnteredKeys->tcur; i++)
	{	
		if(i == findPos)
		{
							
			for(j = i; j < pEnteredKeys->tcur + 1; j++)
			{
				helpMas[j+1] = pEnteredKeys->text[j];
			}
			
			for(j = i; j < pEnteredKeys->tcur + 1; j++)
			{
				pEnteredKeys->text[j+1] = helpMas[j+1];
			
			}
			
			pEnteredKeys->text[findPos] = ' ';
			
		}
	}
		
}


/*******************************************
/* Function name: AddChar() 
/* Author: desia
/* Params: position in array, entered char
/* Functionality: insert a character in an 
* 				   array from given index
********************************************/

void AddChar(int findPos, char newchar, EnteredText_t *pEnteredKeys) 
{
	pEnteredKeys = GlobalGet();
	char help[256];
	int i = 0;
	int j = 0;


	bzero(help,256);
	
	for(i = 0; i < pEnteredKeys->tcur; i++)
	{	
		if(i == findPos)
		{
			j = i;
						
			while(j != pEnteredKeys->tcur)
			{
				help[j+1] = pEnteredKeys->text[j];
				j++;
			}
			help[j+1] = '\0';
					
			for(j = i; j < pEnteredKeys->tcur; j++)
			{
				pEnteredKeys->text[j+1] = help[j+1];
			
			}
	
			pEnteredKeys->text[findPos] = newchar;
			
		}
	}
}

#endif
