/* $Id 2015-11-7 13:54:28 ldlan $ */
#ifndef _STACK_H
#define _STACK_H

typedef char* stack_ele_type;

typedef struct _stack
{
	stack_ele_type* ele;
	int top;
	int stack_size;
}stack_t;

/** 
 * creates and inits a stack 
 */
stack_t create_stack();

/** 
 * push element
 * @returns 1 success, 0 failed
 */
int stack_push(stack_t* _stack, stack_ele_type e);

/**
 * pop element from  stack
 */
stack_ele_type stack_pop(stack_t* _stack);

/** 
 * clear stack
 */
void clear_stack(stack_t* _stack);

/** 
 * destroy stack
 */
void destroy_stack(stack_t* _stack);

/**
 * create a new element of stack
 */
stack_ele_type create_stack_element(const char* dup);

/** 
 * destory element
 */
void destroy_stack_element(stack_ele_type e);
#endif
