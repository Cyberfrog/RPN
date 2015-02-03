#include "../StackADT/stack.h"
typedef struct equation Equation;
typedef struct result Result;

struct result {
  int error;
  int status;
};

struct equation
{
	int oprand1;
	int oprand2;
	char opretor;
};

Result evaluate(char *expression);
Stack spliteBySpace(char* expression);
Stack tokenize(char* expression);
Equation createEquation(Stack ,char );
int* evaluateEquation(Equation);

