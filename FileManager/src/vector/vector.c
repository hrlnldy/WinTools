/* $Id 2014-9-20 22:16:33 ldlan $ */
#include "vector.h"
#include "../error/error.h"
#include <stdlib.h>
#include <string.h>

void init_vector(vector_t* _vec)
{
	if(!_vec) {
		p_error(0, "arguemnt error in function: init_vector");
		return;
	}
	_vec->top = 0;
	_vec->vec = 0;
	_vec->number = 0;
	_vec->size = 0;
}

void push_back(vector_t* _vec, vector_ele_type t)
{
	vector_t new_vec;
	init_vector(&new_vec);

	if(!_vec || !t) {
		p_error(0, "arguemnt error in \
function: push_back");
		return;
	}
	if(_vec->number >= _vec->size) {
		new_vec.size = (_vec->size+4)*3/2;
		new_vec.vec = (vector_ele_type*)malloc(sizeof(vector_ele_type) * new_vec.size);  // realloc
		if(new_vec.vec == 0) {
			p_error(0, "resize to alloc memory failed in \
function: push_back");
			return;
		}

		if(!vector_copy(_vec, &new_vec))  /** copy _vec to new_vec */
			return;

		_vec->number = 0;      // the element completely copy to new vec.
		destroy_vector(_vec);  /** release vector memory and element memory */

		*_vec = new_vec;
	}
	_vec->vec[(_vec->number++ + _vec->top)%_vec->size] = t;
}

vector_ele_type pop_front(vector_t* _vec)
{
	int ind;

	if(!_vec) {
		p_error(0, "arguemnt error in function: vector_copy");
		return 0;
	}
	if(_vec->number <= 0) return 0;

	ind = _vec->top++;

	_vec->top %= _vec->size;
	_vec->number--;

	return _vec->vec[ind];
}

int vector_copy(vector_t* s_vec, vector_t* d_vec)
{
	int sn, dn;

	if(!s_vec || !d_vec) {
		p_error(0, "arguemnt error in function: vector_copy");
		return 0;
	}
	if(s_vec->number > d_vec->size) { /** source vectory memory size 
										small than destination */
		p_error(0, "destination vector is not enough to copy,\
function: vector_copy");
		return 0;
	}
	for(dn=0, sn = s_vec->top;  /** source vec top copy start destination vec start */
		sn<(s_vec->number+s_vec->top); 
		++sn, ++dn) 
		d_vec->vec[dn] = s_vec->vec[sn%s_vec->size];

	d_vec->top = 0;
	d_vec->number = s_vec->number;

	return 1;
}

void destroy_vector(vector_t* _vec)
{
	vector_ele_type e;

	if(!_vec) return;

	while (e = pop_front(_vec))
		free(e);

	if(_vec->vec)
	free(_vec->vec);
	_vec->vec = 0;
	_vec->top = 0;
	_vec->number = 0;
	_vec->size = 0;
}

void clear_vector(vector_t* _vec)
{
	if(!_vec) return;
	
	_vec->top = 0;
	_vec->number = 0;
}

/**
 * create a new vector element
 */
vector_ele_type create_vector_element(const char* name, time_t wtime)
{
	vector_ele_type new_vec_ele = (vector_ele_type)malloc(sizeof(cm_type));
	new_vec_ele->name = _strdup(name);
	new_vec_ele->wtime = wtime;
	return new_vec_ele;
}

/** destory vector element 
 */
void destroy_vector_element(vector_ele_type e)
{
	if(e == NULL) return;
	else
	{
		free(e->name);
		free(e);
	}
}