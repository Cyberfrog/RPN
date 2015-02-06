#include "../StackADT/stack.h"
typedef struct equation Equation;
typedef struct status Status;
typedef struct token Token;
typedef void(Process)(LinkedList *,Stack s,char*);

struct status {
  int error;
  int result;
};

struct token {
  char* value;
  Process *p;
};

struct equation
{
	int oprand1;
	int oprand2;
	char opretor;
};

Status evaluate(char *expression);
Stack tokenize(char* expression);
Equation createEquation(Stack bottle,char *oprator );
int* evaluateEquation(Equation);
LinkedList tokenize_infix(char *expression);
Token * creatToken(void *,Process*);
void processNumber(LinkedList* outputQueue,Stack bottle,char* Number);
void processOprator(LinkedList *outputQueue,Stack bottle,char * oprator);
int getPrecidence(char *oprator);
void pushInfixToken(char *expression,int index,int sizeOftoken, LinkedList * tokenized, Process* p);
int hasHighPrecedence(Stack bottle,char* oprator);