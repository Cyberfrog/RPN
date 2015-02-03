#include "expr_assert.h"
#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void test_evaluate_returns_5_for_2_3_Plus (){
	char * expression ="2 3 +";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 5);
}
void test_evaluate_returns_1_for_2_3_MINUS (){
	char * expression ="2 3 -";
	Status result  =  evaluate(expression);
	assertEqual(result.result, -1);
}
void test_evaluate_returns_6_for_2_3_multiply (){
	char * expression ="2 3 *";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 6);
}
void test_evaluate_returns_0_for_2_3_divide (){
	char * expression ="2 3 /";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 0);
}
void test_evaluate_returns_minus5_for_2_3_4_plus_minus (){
	char * expression ="2 3 4 + -";
	Status result  =  evaluate(expression);
	assertEqual(result.result, -5);
}
void test_evaluate_returns_120_for_1_2_3_4_5_mul_mul_mul_mul (){
	char * expression ="1 2 3 4 5 * * * *";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 120);
}
void test_evaluate_returns_60_for_20_20_20_add_add (){
	char * expression ="20 20 20 + +";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 60);
}
void test_evaluate_returns_600_for_200_200_200_add_add (){
	char * expression ="200 200 200 + +";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 600);
}
void test_splitBySpace_returns_Stack_all_splited_Strings_ (){
	char * expression ="23 hi jo";
	Stack result  =  spliteBySpace(expression);
	char * poped =pop(result);
	assertEqual(strcmp(poped,"23"),0);
	poped =pop(result);
	assertEqual(strcmp(poped,"hi"),0);
	poped =pop(result);
	assertEqual(strcmp(poped,"jo"),0);
}
void test_tokenize_returns_seprated_token(){
	char * expression ="22 33 55+-";
	Stack result  =  tokenize(expression);
	char * poped =pop(result);
	assertEqual(strcmp(poped,"22"),0);
	poped =pop(result);
	assertEqual(strcmp(poped,"33"),0);
	poped =pop(result);
	assertEqual(strcmp(poped,"55"),0);
	poped =pop(result);
	assertEqual(strcmp(poped,"+"),0);
	poped =pop(result);
	assertEqual(strcmp(poped,"-"),0);
}
void test_createEquation_returns_the_Equation(){
	int *op1=malloc(sizeof(int)),*op2=malloc(sizeof(int));
	char op='+';
	Equation e;
	Stack s=createStack();
	*op1=22,*op2=23;
	push(s,op1);
	push(s,op2);
	e = createEquation(s,op);
	assertEqual(e.oprand1,22);
	assertEqual(e.oprand2, 23);
	assertEqual(e.opretor, op);
}
void test_evaluateEquation_returns_45_for_22_23_plus_equation(){
	int *op1=malloc(sizeof(int)),*op2=malloc(sizeof(int));
	int *result;
	char op='+';
	Equation e;
	Stack s=createStack();
	*op1=22,*op2=23;
	push(s,op1);
	push(s,op2);
	e = createEquation(s,op);
	result = evaluateEquation(e);
	assertEqual(*result,45);
}
void test_evaluateEquation_returns_5_for_25_20_minus_equation(){
	int *op1=malloc(sizeof(int)),*op2=malloc(sizeof(int));
	int *result;
	char op='-';
	Equation e;
	Stack s=createStack();
	*op1=25,*op2=20;
	push(s,op1);
	push(s,op2);
	e = createEquation(s,op);
	result= evaluateEquation(e);
	assertEqual(*result,5);
}
// ----------------------------------------------version2Test-----------------------------------------------------------
void test_evaluate_returns_14_for_5_1_2_plus_4_mul_plus_3_minus (){
	char * expression ="5 1 2 + 4 * + 3 -";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 14);
}
void test_evaluate_returns_7_for_2_2_2_mul_2_minus_3_plus_plus (){
	char * expression ="2 2 2 * 2 - 3 + +";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 7);
}
void test_evaluate_returns_20_for_2_2_2_2_2_mul__mul_2_plus_plus_2_minus_mul (){
	char * expression ="2 2 2 2 2 * * 2 + + 2 - *";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 20);
}
void test_evaluate_returns_0_for_2_2_minus_2_2_2_mul_2_minus_minus_minus (){
	char * expression ="2 2 - 2 2 2 * 2 - - -";
	Status result  =  evaluate(expression);
	assertEqual(result.result, 0);
}