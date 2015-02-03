#include "../StackADT/stack.h"
typedef struct equation Equation;
struct equation
{
	int oprand1;
	int oprand2;
	char opretor;
};
int evaluate(char *expression);
Stack spliteBySpace(char* expression);
Stack tokenize(char* expression);
Equation createEquation(Stack ,char );
int* evaluateEquation(Equation);

