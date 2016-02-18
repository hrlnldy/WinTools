/* $Id 2014-9-20 22:16:24 ldlan $ */
#ifndef _VECTOR_H
#define _VECTOR_H

#include <time.h>

//typedef char* vector_ele_type;

typedef struct _vector_ele_type
{
	
	char* name;		/** name of file */
	
	time_t wtime;	/** last write time */

}cm_type, *vector_ele_type;

/** 
 * use circular array
 */

typedef struct _vector
{
	vector_ele_type *vec;	/** pointer to vector type */
	int top;				/** vector_t top, first element in vector */
	int number;				/** element counter */
	int size;				/** vector memory size */
}vector_t;

/**
 * initialize vector function must call before
 * use vector.
 */
void init_vector(vector_t* _vec);

/**
 * push back vector element.
 */
void push_back(vector_t* _vec, vector_ele_type t);

/** pop front */
vector_ele_type pop_front(vector_t* _vec);

/**
 * copy form s_vec to d_vec
 *
 *@return 0 failed, other success.
 */
int vector_copy(vector_t* s_vec, vector_t* d_vec);

/**
 * clear vector without release memery
 */
void clear_vector(vector_t* _vec);

/** 
 * release memory of vector and element
 */
void destroy_vector(vector_t* _vec);

/** destory vector element 
 */
void destroy_vector_element(vector_ele_type e);

/**
 * create a new vector element
 */
vector_ele_type create_vector_element(const char* name, time_t wtime);

#endif /* _VECTOR_H */