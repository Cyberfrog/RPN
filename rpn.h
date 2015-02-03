#include "../StackADT/stack.h"
typedef struct equation Equation;
typedef struct status Status;

struct status {
  int error;
  int result;
};

struct equation
{
	int oprand1;
	int oprand2;
	char opretor;
};

Status evaluate(char *expression);
Stack spliteBySpace(char* expression);
Stack tokenize(char* expression);
Equation createEquation(Stack ,char );
int* evaluateEquation(Equation);

