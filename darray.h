#ifndef darray_h
#define darray_h

#ifndef typedef_byte
#define typedef_byte
typedef unsigned char byte;
#endif

typedef struct
{
	byte element_size;
	unsigned int length;
	byte* array; // array of bytes, grouped by defined size of the stored type
} darray;

void dar_init(darray* dar, byte element_size);
void dar_free(darray* dar);
void dar_resize(darray* dar, unsigned int new_length);

const byte* dar_get(darray* dar, unsigned int position);
#define DAR_GET(type_name, pointer_to_a_darray, position) ((type_name*)dar_get(pointer_to_a_darray, position))
void dar_set(darray* dar, unsigned int position, const byte* value);

void dar_insert(darray* dar, unsigned int position, const byte* value);
void dar_del(darray* dar, unsigned int position);

void dar_set_arr(darray* dar, unsigned int position, const byte* array, unsigned int arr_length);
void dar_insert_arr(darray* dar, unsigned int position, const byte* array, unsigned int arr_length);
void dar_del_arr(darray* dar, unsigned int position, unsigned int arr_length);

void dar_push(darray* dar, const byte* value);
const byte* dar_pull(darray* dar);
#define DAR_PULL(type_name, pointer_to_a_darray) ((type_name*)dar_pull(pointer_to_a_darray))
void dar_push_arr(darray* dar, const byte* array, unsigned int arr_length);

#endif