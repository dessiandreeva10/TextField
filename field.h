#ifndef FIELD_H_
#define FIELD_H_

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define INIT_OK 1
#define BEGIN_OK 2
#define EXIT_SUCCESSFULL -1
#define TAB 9
#define ESC 27 
#define SPACE 32
#define BACKSPACE 127
#define BUFFER_MAXSIZE 256

typedef struct EnteredKeys{
	int cursor; 
	char text[256]; 
	int begin; 
	int tcur; 
	int cursorVisible; 
	int endT; 
}EnteredText_t;

EnteredText_t *pEnteredKeys = NULL;

#define CLEAR() printf("\033[H\033[J")
#define GOTOXY(x,y) printf("\033[%d;%dH", (x), (y))
#define MOVERIGHT() printf("\033[C")
#define MOVELEFT() printf("\033[D")

EnteredText_t *GlobalGet();
void CleanBuffer(EnteredText_t *pEnteredKeys);
void PrintField();
void PrintMessage();
EnteredText_t *InitGlobalStruct(EnteredText_t **ppEnteredKeys);
void PrintAfterAdded(EnteredText_t *pEnteredKeys);
void PrintAfterDelete(int findPos, EnteredText_t *pEnteredKeys);
void CheckWhereToAddSpace(int findPos, EnteredText_t *pEnteredKeys);
void ArrowsMovingKeys(char ident, EnteredText_t *pEnteredKeys);
void EnterCharInSomePosition(char newchar, int position, EnteredText_t *ppEnteredKeys);
void RemoveChar(int findPos, EnteredText_t *pEnteredKeys);
void PrintAfterBS(int findPos, EnteredText_t *pEnteredKeys);
void PrintResult(int begin, int end, EnteredText_t *pEnteredKeys);
void AddSpace(int findPos, EnteredText_t *pEnteredKeys);
void AddChar(int findPos, char newchar, EnteredText_t *pEnteredKeys);

int  Begin(EnteredText_t *pEnteredKeys);
void EnteredText(char ret, EnteredText_t *pEnteredKeys);
void LeftKeyPressed(EnteredText_t *pEnteredKeys);
void RightKeyPressed(EnteredText_t *pEnteredKeys);
void DeleteKeyPressed(EnteredText_t *pEnteredKeys);
void HomeKeyPressed(EnteredText_t *pEnteredKeys);
void EndKeyPressed(EnteredText_t *pEnteredKeys);
void SpaceKeyPressed(EnteredText_t *pEnteredKeys);
void BackpaceKeyPressed(EnteredText_t *pEnteredKeys);

#endif
