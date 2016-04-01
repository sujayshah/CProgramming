#include "vector.h"
#include <stdlib.h>


vector_t * createVector(int initialSize)
{
	vector_t* my_vector = (vector_t*) malloc(sizeof(vector_t));
	my_vector->maxSize = initialSize; 
	my_vector->size = 0;
	my_vector->array = malloc(sizeof(int)*initialSize);
	return my_vector;
}

void destroyVector(vector_t * vector)
{
	free(vector->array);
	free(vector);
}

void resize(vector_t * vector)
{
	vector->maxSize = 2*vector->maxSize;
	vector->array = realloc(vector->array, sizeof(int)*vector->maxSize);
}

void push_back(vector_t * vector, int element)
{
	if(vector->size == vector->maxSize)
	{
		resize(vector);
	}
	vector->size = vector->size+1;
	vector->array[vector->size-1] = element;
}

int pop_back(vector_t * vector)
{
	if(vector->size == 0)
	{
		return 0;
	}
	vector->size = vector->size-1;
	return vector->array[vector->size];
}

int access(vector_t * vector, int index)
{
	if(index < 0 || index > vector->size)
	{
		return 0;
	}
	return vector->array[index];
}

