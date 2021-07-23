#include "darray.h"
#include <stdlib.h>


void dar_init(darray* dar, byte element_size)
{
	dar->element_size = element_size;
	dar->length = 0;
	dar->array = (byte*) malloc(0);
}

void dar_free(darray* dar)
{
	free(dar->array);
	dar->length = 0;
}

void dar_resize(darray* dar, unsigned int new_length)
{
	realloc(dar->array, dar->element_size * new_length);
	dar->length = new_length;
}




const byte* dar_get(darray* dar, unsigned int position)
{
	if (position >= dar->length) return 0;
	return &dar->array[position * dar->element_size];
}

void dar_set(darray* dar, unsigned int position, const byte* value)
{
	if (position >= dar->length) return;
	for (int i = 0; i < dar->element_size; ++i)
		dar->array[position * dar->element_size + i] = value[i];
}




void dar_insert(darray* dar, unsigned int position, const byte* value)
{
	if (position >= dar->length) return;
	dar_resize(dar, dar->length+1);
	for (int i = dar->length-2; i >= 0; --i)
		if (i >= position) dar_set(dar, i+1, dar_get(dar, i));
	dar_set(dar, position, value);
}

void dar_del(darray* dar, unsigned int position)
{
	if (position >= dar->length) return;
	for (int i = 0; i < dar->length; ++i)
		if (i > position) dar_set(dar, i-1, dar_get(dar, i));
	dar_resize(dar, dar->length-1);
}




void dar_set_arr(darray* dar, unsigned int position, const byte* array, unsigned int arr_length)
{
	for (int i = 0; i < arr_length & i < dar->length; ++i)
		dar_set(dar, position + i, (byte*)&array[dar->element_size * i]);
}

void dar_insert_arr(darray* dar, unsigned int position, const byte* array, unsigned int arr_length)
{
	for (int i = 0; i < arr_length; ++i)
		dar_insert(dar, position + i, (byte*)&array[dar->element_size * i]);
}

void dar_del_arr(darray* dar, unsigned int position, unsigned int arr_length)
{
	if (position >= dar->length) return;
	for (int i = 0; i < arr_length && position < dar->length; ++i)
		dar_del(dar, position);
}




void dar_push(darray* dar, const byte* value)
{
	dar_resize(dar, dar->length+1);
	dar_set(dar, dar->length-1, value);
}

const byte* dar_pull(darray* dar)
{
	return dar_get(dar, dar->length-1);
}

void dar_push_arr(darray* dar, const byte* array, unsigned int arr_length)
{
	dar_resize(dar, dar->length + arr_length);
	dar_set_arr(dar, (dar->length-1 - arr_length + 1), array, arr_length);
}