#include "expr_assert.h"
#include "rpn.h"
#include <stdio.h>
#include <string.h>
void test_evaluate_returns_5_for_2_3_Plus (){
	char * expression ="2 3 +";
	int result  =  evaluate(expression);
	assertEqual(result, 5);
}
void test_evaluate_returns_1_for_2_3_MINUS (){
	char * expression ="2 3 -";
	int result  =  evaluate(expression);
	assertEqual(result, -1);
}
void test_evaluate_returns_6_for_2_3_multiply (){
	char * expression ="2 3 *";
	int result  =  evaluate(expression);
	assertEqual(result, 6);
}
void test_evaluate_returns_0_for_2_3_divide (){
	char * expression ="2 3 /";
	int result  =  evaluate(expression);
	assertEqual(result, 0);
}
void test_evaluate_returns_minus5_for_2_3_4_plus_minus (){
	char * expression ="2 3 4 + -";
	int result  =  evaluate(expression);
	assertEqual(result, -5);
}
void test_evaluate_returns_120_for_1_2_3_4_5_mul_mul_mul_mul (){
	char * expression ="1 2 3 4 5 * * * *";
	int result  =  evaluate(expression);
	assertEqual(result, 120);
}
void test_evaluate_returns_60_for_20_20_20_add_add (){
	char * expression ="20 20 20 + +";
	int result  =  evaluate(expression);
	assertEqual(result, 60);
}
void test_evaluate_returns_600_for_200_200_200_add_add (){
	char * expression ="200 200 200 + +";
	int result  =  evaluate(expression);
	assertEqual(result, 600);
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
