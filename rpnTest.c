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
	char *op="+";
	Equation e;
	Stack s=createStack();
	*op1=22,*op2=23;
	push(s,op1);
	push(s,op2);
	e = createEquation(s,op);
	assertEqual(e.oprand1,22);
	assertEqual(e.oprand2, 23);
	assertEqual(e.opretor, *op);
}
void test_evaluateEquation_returns_45_for_22_23_plus_equation(){
	int *op1=malloc(sizeof(int)),*op2=malloc(sizeof(int));
	int *result;
	char *op="+";
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
	char *op="-";
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
// ----------------------------------------------version3Test-----------------------------------------------------------
void test_evaluate_returns_error_1_for_extra_optraor (){
	char * expression ="2 2 - 2 2 2 * 2 - - - - -";
	Status result  =  evaluate(expression);
	assertEqual(result.error, 1);

	assertEqual(result.result, 0);
}

void test_evaluate_returns_error_minus_1_for_extra_optrand (){
	char * expression ="2 2 - 2 2 2 * 2 - - ";
	Status result  =  evaluate(expression);
	assertEqual(result.error, -1);

	assertEqual(result.result, 0);
}
// ---------------------------------------------vesion 4Testion---------------------
void preProcess(LinkedList* l,Stack s ,char* c){}
void test_creatToken_retuns_pointer_to_empty_token (){
	char * d = "hii";
	Token *t = creatToken(d,preProcess);
	assert(t->value==d);
	assert(t->p== preProcess);
}
void test_toknized_infix_retun_list_of_tokens_in_infix_expression(){
	char * expression ="2+1*(3+2)";
	LinkedList result  =  tokenize_infix(expression);
	assertEqual(strcmp(((Token*)(result.head->data))->value, "2"),0);
	assertEqual(strcmp(((Token*)(result.tail->data))->value, ")"),0);
}
// void test_toknized_infix_understand_negative_Number(){
// 	char * expression ="-2 + 1 * (3+2)";
// 	LinkedList result  =  tokenize_infix(expression);
// 	assertEqual(strcmp(((Token*)(result.head->data))->value, "-2"),0);
// 	assertEqual(strcmp(((Token*)(result.tail->data))->value, ")"),0);
// }
void processor(LinkedList * queue,Stack s,char* Number){

}
void test_pushInfixToken_push_token_from_expression_in_stack(){
	Stack s=createStack();
	LinkedList tokens =createList();
	char* expression="22 + 33";
	Token *t;
	pushInfixToken(expression,3,1, &tokens, processor);
	t=tokens.head->data;
	assertEqual(*t->value,expression[3]);
	assert(t->p==processor);
}

void test_processNumber_Push_number_in_the_stack(){
	LinkedList l=createList();
	char * num="123";
	processNumber(&l,(Stack){},num);
	assertEqual(*(int*)(l.tail->data) ,123);
}
void test_getPrecidence_returns_precidenceOf_oprator(){
	char * oprator="+";
	int p=getPrecidence(oprator);
	assertEqual(p ,2);
}
void test_getPrecidence_MINUS_has_precidenceOf_2(){
	char * oprator="-";
	int p=getPrecidence(oprator);
	assertEqual(p ,2);
}
void test_getPrecidence_Mul_has_precidenceOf_3(){
	char * oprator="*";
	int p=getPrecidence(oprator);
	assertEqual(p ,3);
}
void test_getPrecidence_bracket_has_precidenceOf_4(){
	char * oprator=")";
	int p=getPrecidence(oprator);
	assertEqual(p ,4);
}
void test_getPrecidence_returns_0_for_nonOprator_charecter_4(){
	char * oprator="a";
	int p=getPrecidence(oprator);
	assertEqual(p ,0);
}
void test_processOprator_push_oprator_in_bottle(){
	Stack bottle =createStack();
	LinkedList queue;
	char* oprator="+";
	processOprator(&queue,bottle,oprator);
	assert((*bottle.top)->data==oprator);
}
// void test_processOprator_pops_higher_precedence_oprator_form_bottlr_and_put_it_in_queue(){
// 	Stack bottle =createStack();
// 	LinkedList queue =createList();
// 	char* oprator="+";
// 	char* h_oprator="/";

// 	processOprator(&queue,bottle,h_oprator);
// 	processOprator(&queue,bottle,oprator);
// 	assert((*bottle.top)->data==oprator);
// 	assert(queue.head->data==h_oprator);
// }
void test_hasHighPrecedence_returns_0_when_oprator_in_bottle_has_low_precedence(){
	Stack bottle =createStack();
	LinkedList queue =createList();
	char* oprator="+";
	char* h_oprator="/";
	push(bottle,oprator);
	assertEqual(hasHighPrecedence(bottle,h_oprator),0);
}
void test_hasHighPrecedence_returns_1_when_oprator_in_bottle_has_high_precedence(){
	Stack bottle =createStack();
	LinkedList queue =createList();
	char* oprator="+";
	char* h_oprator="/";
	push(bottle,h_oprator);
	assertEqual(hasHighPrecedence(bottle,oprator),1);
}
void test_hasHighPrecedence_returns_0_when_oprator_in_bottle_has_same_precedence(){
	Stack bottle =createStack();
	LinkedList queue =createList();
	char* oprator="+";
	char* h_oprator="-";
	push(bottle,h_oprator);
	assertEqual(hasHighPrecedence(bottle,oprator),0);
}