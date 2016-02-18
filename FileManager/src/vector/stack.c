/* $Id 2015-11-7 13:59:22 ldlan $ */
/** 
 * creates and inits a stack 
 */
#include "../error/error.h"
#include "stack.h"
#include <string.h>
#include <malloc.h>

/** 
 * creates and inits a stack 
 */
stack_t create_stack()
{
	stack_t _stack;

	_stack.ele = 0;
	_stack.top = 0;
	_stack.stack_size = 0;

	return _stack;
}

/** 
 * push element
 * @returns 1 success, 0 failed
 */
int stack_push(stack_t* _stack, stack_ele_type e)
{
	stack_t new_stack = create_stack();  // // for realloc.
	if(_stack->top+1 >= _stack->stack_size)
	{
		new_stack.stack_size = (_stack->stack_size+4)*3/2;
		new_stack.ele = (stack_ele_type*)realloc(_stack->ele, sizeof(stack_ele_type)*new_stack.stack_size);
		if(new_stack.ele == 0 && new_stack.stack_size)  // realloc failed if request size not equas zero, try malloc
		{
			new_stack.ele = (stack_ele_type*)malloc(sizeof(stack_ele_type)*new_stack.stack_size);
		}
		if(new_stack.ele == 0 && new_stack.stack_size)  // alloc memory failed
		{
			p_error(0, "resize to alloc memory failed in \
					   function: push_back");
			return 0;  // push failed
		}

		if(new_stack.ele != _stack->ele)  // stack copy if need, reserved
		{			
		}
		new_stack.top = _stack->top;
		*_stack = new_stack;
	}
	_stack->ele[_stack->top++] = e;
	return 1;
}

/**
 * pop element from  stack
 */
stack_ele_type stack_pop(stack_t* _stack)
{
	if(!_stack) {
		p_error(0, "arguemnt error in function: vector_copy");
		return (stack_ele_type)0;
	}
	if(_stack->top <= 0)
		return (stack_ele_type)0;

	return _stack->ele[--_stack->top];
}

/** 
 * clear stack
 */
void clear_stack(stack_t* _stack)
{
	if(!_stack)
		return;
	_stack->top = 0;
}

/** 
 * destroy stack
 */
void destroy_stack(stack_t* _stack)
{
	stack_ele_type e;
	while ((e = stack_pop(_stack)))
		free(e);
	free(_stack->ele);

	_stack->ele = 0;
	_stack->top = 0;
	_stack->stack_size = 0;
}


/**
 * create a new element of stack
 */
stack_ele_type create_stack_element(const char* dup)
{
	return _strdup(dup);
}

/** 
 * destory element
 */
void destroy_stack_element(stack_ele_type e)
{
	if(e != 0)
		free(e);
}