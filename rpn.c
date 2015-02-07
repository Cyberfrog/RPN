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

Status evaluate(char *expression){
	Stack tokenized = tokenize(expression);
	Stack bottle =  createStack();
	Equation e;
	int *number;
	char * element=pop(tokenized);
	
	while(element){
		if(isOprator(*element)){
			e =createEquation(bottle,element);
			if(!e.oprand1)
				return(Status){1,0};
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

	return *(bottle.count)==1?(Status){0,*(int*)pop(bottle)}:(Status){-1,0};
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

Equation createEquation(Stack bottle ,char *oprator){
	int *op2 = (int*)(pop(bottle));
	int *op1 =(int*)(pop(bottle));
	if(op2&&op1){
		Equation e={*op1,*op2,*oprator};
		free(op2);
		free(op1);
		return e;
	}
	return (Equation){0,0,0};
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
// -----------------------------------------------------------------------version 4---------------------------------------------
Token * creatToken(void* data ,Process *p){

	Token * t=(calloc(1, sizeof(Token)));
	t->value =data;
	t->p = p;
	return t;
}
int isInfixOprator(char op){
	return isOprator(op);
}
void pushInfixToken(char *expression,int index,int sizeOftoken, LinkedList * tokenized, Process* p){
	if(sizeOftoken>0){
		Token* token =creatToken(strCopy(&expression[index],sizeOftoken),p);
		add_to_list(tokenized, create_node(token));
	}
}

void processNumber(LinkedList *outputQueue,Stack bottle,char* Number){
	add_to_list(outputQueue,create_node(Number));
}

void processOprator(LinkedList *outputQueue,Stack bottle,char * oprator){
	while(hasHighPrecedence(bottle,oprator)){
		add_to_list(outputQueue,create_node(pop(bottle)));
	}
	push(bottle,oprator);

}
void processParenthesis(LinkedList *outputQueue,Stack bottle,char * parenthesis){
	if(isRightParenthesis(parenthesis)){
		while(!isParenthesis((*bottle.top)->data)){
			add_to_list(outputQueue,create_node(pop(bottle)));
		}
		pop(bottle);
		return;
	}
	push(bottle,parenthesis);
}

int hasHighPrecedence(Stack bottle, char *oprator){
	return *bottle.top?getPrecidence((*bottle.top)->data)>=getPrecidence(oprator):0;
}

LinkedList tokenize_infix(char *expression){
	LinkedList tokenized=createList();
	int length =  strlen(expression);
	int index,currentIndex=-1;

	for(index=0;index<length;index++){
		if(!isDigit(expression[index])){
			pushInfixToken(expression,currentIndex+1,(index-currentIndex)-1, &tokenized,processNumber);
			currentIndex = index;

		}
	
		if(isInfixOprator(expression[index])){
			pushInfixToken(expression, index,1,&tokenized,processOprator);		
		}
		if(isParenthesis(&expression[index])){
			pushInfixToken(expression, index,1,&tokenized,processParenthesis);		

		}
	}

	pushInfixToken(expression,currentIndex+1,(index-currentIndex)-1, &tokenized,processNumber);
	return tokenized;	
}

int getPrecidence(char * oprator){
	switch(*oprator){
		case '+':;
		case '-':return 2;
		case '*':;
		case '/':return 3;
		case '(':;
		case ')':return 1;
	}
	return 0;
}

void  printQueue(LinkedList queue){
	void print(char *value){
		printf("%s\n",value );
	};
	traverse(queue,print);
}

char * infixToPostfix(char * expression){
	LinkedList queue = createList();
	LinkedList tokenized = tokenize_infix(expression);
	Stack operators  = createStack();
	void processToken(Token *t){
		(t->p)(&queue,operators,t->value);	
	}
	traverse(tokenized,processToken);
	popOpratorsToQueue(&queue,operators);
	// printQueue(queue);
	return stringifyQueue(queue);
}
char* stringifyQueue(LinkedList queue){
	int totalLength =0;
	char * output = NULL;
	Node *walker = queue.head;
	void catString(char* token){
		output =strcat(output,token);
		totalLength-=(strlen(token)+1);
		totalLength && (output = strcat(output," "));
	};

	while(walker!=NULL){
		totalLength+=(strlen(walker->data)+1);
		walker=walker->next;
	}
	output = (char *)calloc(sizeof(char),totalLength);
	
	traverse(queue,catString);
	return output;
}
int isRightParenthesis(char *oprator){
	return *oprator ==')';
}
int isParenthesis(char *oprator){
	return *oprator==')'||*oprator=='(';
}
void popOpratorsToQueue(LinkedList *quque,Stack bottle){
	while(*bottle.top!=NULL){
		add_to_list(quque, create_node(pop(bottle)));
	}
}
