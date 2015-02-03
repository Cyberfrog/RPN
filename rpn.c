#include "rpn.h"
#include <string.h>
#include <stdlib.h>

const char SPACE=' ';


int isDigit(char d){
	return d>='0'&&d<='9';
}

int isOprator(char d){
	return d=='+'||d=='-'||d=='*'||d=='/';
}

int evaluate(char *expression){
	Stack tokenized = tokenize(expression);
	Stack bottle =  createStack();
	Equation e;
	int *number;
	char * element=pop(tokenized);
	while(element){
		if(isOprator(*element)){
			e =createEquation(bottle,element[0]);
			push(bottle,evaluateEquation(e));
		}
		else{
			number =malloc(sizeof(int));
			*number = atoi(element); 
			push(bottle, number);
		}
		free(element);
		element = pop(tokenized);
	}
	return *(int*)pop(bottle);
}

char * strCopy(char * source,int noOfChar){
	int i;
	char * dest =malloc(sizeof(char)*(noOfChar+1));
	for (i=0;i<noOfChar;i++){
		dest[i]=source[i];
	}
	dest[i] = '\0';
	return dest;
}




void pushToken(char *expression,int index,int sizeOftoken, Stack * tokenized){
	if(sizeOftoken>0){
		char * token;
		token = strCopy(&expression[index],sizeOftoken);
		push(*tokenized, token);

	}
}

Stack tokenize(char* expression){
	Stack tokenized = createStack();
	int length =  strlen(expression);
	int index,currentLength=length;

	for(index=length-1;index>=0;index--){
	
		if(!isDigit(expression[index])){
			pushToken(expression,index+1,(currentLength-index)-1, &tokenized);
			currentLength = index;
		}
	
		if(isOprator(expression[index])){
			pushToken(expression, index,1,&tokenized);		
		}
	}
	pushToken(expression,index+1,(currentLength-index)-1, &tokenized);
	
	return tokenized;
}

Equation createEquation(Stack bottle ,char oprator){
	int *op2 = (int*)(pop(bottle));
	int *op1 =(int*)(pop(bottle));
	Equation e={*op1,*op2,oprator};
	free(op2);
	free(op1);
	return e;
}
int* evaluateEquation(Equation e){
	int* result = (int*)malloc(sizeof(int));
	switch(e.opretor){
		case '+':
			*result =e.oprand1+e.oprand2;
			return result;
		case '-':
			*result =e.oprand1-e.oprand2;
			return result;
		case '*':
			*result =e.oprand1*e.oprand2;
			return result;
		case '/':
			*result =e.oprand1/e.oprand2;
	}	
	return result;		
}

Stack spliteBySpace(char* expression){
	Stack s = createStack();
	char * string;
	int length =  strlen(expression);
	int i,spaceIndex=length;
	for(i=length-1;i>=0;i--){
		if(expression[i]==SPACE){
			string = strCopy(&expression[i+1],(spaceIndex-i)-1);
			push(s, string);
			spaceIndex =i;
		}
	}
	string = strCopy(&expression[i+1],(spaceIndex-i)-1);
	push(s, string);
	return s;
}