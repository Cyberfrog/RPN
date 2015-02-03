#include "rpn.h"
#include <string.h>
#include <stdlib.h>

const char SPACE=' ';
int evaluate(char *expression){
	Stack seprated = tokenize(expression);
	Stack container =  createStack();
	int count=0;
	int op1,op2;
	int * result ;
	char * element=pop(seprated);
	while(element){
		switch(element[0]){
			case '+' :
				op2 = *(int*)(pop(container));
				op1 =*(int*)(pop(container));
				result = (int*)malloc(sizeof(int));
				*result = op1+op2;
				push(container,result);
			break;
			case '-': 
				op2 = *(int*)(pop(container));
				op1 =*(int*)(pop(container));
				result = (int*)malloc(sizeof(int));
				*result = op1-op2;
				push(container,result);
			break;
			case '*': 
				op2 = *(int*)(pop(container));
				op1 =*(int*)(pop(container));
				result = (int*)malloc(sizeof(int));
				*result = op1*op2;
				push(container,result);
			break;
			case '/': 
				op2 = *(int*)(pop(container));
				op1 =*(int*)(pop(container));
				result = (int*)malloc(sizeof(int));
				*result = op1/op2;
				push(container,result);
			break;
			default:
				result =malloc(sizeof(int));
				*result = atoi(element); 
				push(container, result);
		}
		free(element);
		element = pop(seprated);
	}
	return *(int*)pop(container);
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
int isDigit(char d){
	return d>='0'&&d<='9';
}
int isOprator(char d){
	return d=='+'||d=='-'||d=='*'||d=='/';
}
Stack tokenize(char* expression){
	Stack s = createStack();
	char * string;
	int length =  strlen(expression);
	int i,lastIndex=length;

	for(i=length-1;i>=0;i--){
		if(!isDigit(expression[i])){
			if(lastIndex-i>=2){
				string = strCopy(&expression[i+1],(lastIndex-i)-1);
				push(s, string);

			}
			lastIndex =i;
		}
		if(isOprator(expression[i])){
			string = strCopy(&expression[i],1);
			push(s, string);
			
		}
	}
	string = strCopy(&expression[i+1],(lastIndex-i)-1);
	push(s, string);

	return s;
}
