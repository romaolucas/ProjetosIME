/*
 * stack.h 
 * INTERFACE: funcoes para manipular a pilha 
 * ATENCAO: Esta interface permite que varias pilhas sejam 
 *          utilizadas simultaneamente.
 */
#include "util.h"
typedef struct stack *Stack;
Stack stackInit(int);
 int  stackEmpty(Stack);
void  stackPush(Stack,float);
float  stackPop(Stack);
CelUtil*  stackTop(Stack);
void  stackFree(Stack);
void  stackDump(Stack); 
void  setStackTop(Stack,float);
CelUtil* getStackTop(Stack);
