#include "septarr.h"
#include <stdlib.h>
#include <string.h>

/*
 * Initial function to construct the data. We have to call septarr_destroy() to
 * destroy (free()) the data after we done with the data.
 */
struct septarr *septarr_init()
{
        struct septarr *ret;

        ret = malloc(sizeof(*ret));
        ret->size = malloc(sizeof(int));
        *ret->size = 0;
        ret->allocated_size = malloc(sizeof(int));
        *ret->allocated_size = SEPTARR_INIT_SIZE;
        ret->data = malloc(sizeof(*ret->data)*SEPTARR_INIT_SIZE);
        ret->data[0] = NULL;

        return ret;
}

/*
 * The function that have responsbility for reallocation of the array inside the
 * data structure.
 */
int septarr_realloc(struct septarr **ptr, int new_allocated_size)
{
        struct septarr_data **new_ptr;
        
        new_ptr = reallocarray((*ptr)->data, new_allocated_size, sizeof(*(*ptr)->data));
        
        if (new_ptr == NULL)
                return -1;
        
        (*ptr)->data = new_ptr;
        *(*ptr)->allocated_size = new_allocated_size;

        return 0;
}

/*
 * Get the size of the array inside the data structure. This is the easiest way to
 * get the size.
 */
int septarr_get_size(struct septarr *ptr)
{
        return *ptr->size;
}

/*
 * Get the allocated size of the array inside the data structure. This is the easiest
 * way to get the allocated size.
 */
int septarr_get_allocated_size(struct septarr *ptr)
{
        return *ptr->allocated_size;
}

/*
 * Get the data type stored in the element of array inside the data structure.
 * Make sure that you are not accessing an out-of-bounds value or you will get
 * undefined behavior (UB). The reason why I did not make this function safe is
 * because I need speed, so we have to use it carefully.
 */
int septarr_get_type(struct septarr *ptr, int index)
{
        return *ptr->data[index]->type;
}

/*
 * The function that will grow the array inside the data structure if we need
 * to grow it.
 */
int septarr_grow_if_needed(struct septarr **ptr)
{
        if (*(*ptr)->size >= *(*ptr)->allocated_size - 1)
                return septarr_realloc(&(*ptr), *(*ptr)->allocated_size + SEPTARR_INIT_SIZE);

        return 0;
}

/*
 * The function that will shrink the array inside the data structure if we need
 * to shrink it.
 */
int septarr_shrink_if_needed(struct septarr **ptr)
{
        if ((*(*ptr)->allocated_size-SEPTARR_INIT_SIZE) >= *(*ptr)->size)
                return septarr_realloc(&(*ptr), *(*ptr)->allocated_size - SEPTARR_INIT_SIZE);

        return 0;
}

// Push an int value to the data structure.
int septarr_push_int(struct septarr **ptr, int value)
{
        int gin = septarr_grow_if_needed(&(*ptr));

        if (gin < 0)
                return gin;

        (*ptr)->data[*(*ptr)->size] = malloc(sizeof(**(*ptr)->data));

        (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->type));
        *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_INT;

        (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->value));
        (*ptr)->data[*(*ptr)->size]->value->int_val = malloc(sizeof(int));
        *(*ptr)->data[*(*ptr)->size]->value->int_val = value;

        *(*ptr)->size += 1;
        (*ptr)->data[*(*ptr)->size] = NULL;

        return 0;
}

// Push a float value to the data structure.
int septarr_push_float(struct septarr **ptr, float value)
{
        int gin = septarr_grow_if_needed(&(*ptr));

        if (gin < 0)
                return gin;

        (*ptr)->data[*(*ptr)->size] = malloc(sizeof(**(*ptr)->data));

        (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->type));
        *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_FLOAT;

        (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->value));
        (*ptr)->data[*(*ptr)->size]->value->float_val = malloc(sizeof(float));
        *(*ptr)->data[*(*ptr)->size]->value->float_val = value;

        *(*ptr)->size += 1;
        (*ptr)->data[*(*ptr)->size] = NULL;

        return 0;
}

// Push a double value to the data structure.
int septarr_push_double(struct septarr **ptr, double value)
{
        int gin = septarr_grow_if_needed(&(*ptr));

        if (gin < 0)
                return gin;

        (*ptr)->data[*(*ptr)->size] = malloc(sizeof(**(*ptr)->data));

        (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->type));
        *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_DOUBLE;

        (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->value));
        (*ptr)->data[*(*ptr)->size]->value->double_val = malloc(sizeof(double));
        *(*ptr)->data[*(*ptr)->size]->value->double_val = value;

        *(*ptr)->size += 1;
        (*ptr)->data[*(*ptr)->size] = NULL;

        return 0;
}

// Push a string (array of char) to the data structure.
int septarr_push_string(struct septarr **ptr, char *value)
{
        int gin = septarr_grow_if_needed(&(*ptr));

        if (gin < 0)
                return gin;

        (*ptr)->data[*(*ptr)->size] = malloc(sizeof(**(*ptr)->data));

        (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->type));
        *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_STRING;

        (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->value));
        (*ptr)->data[*(*ptr)->size]->value->string_val = malloc(sizeof(char)*strlen(value)+1);
        strcpy((*ptr)->data[*(*ptr)->size]->value->string_val, value);

        *(*ptr)->size += 1;
        (*ptr)->data[*(*ptr)->size] = NULL;

        return 0;
}

// Push a septarr to the data structure.
int septarr_push_septarr(struct septarr **ptr, struct septarr *value)
{
        int gin = septarr_grow_if_needed(&(*ptr));

        if (gin < 0)
                return gin;

        (*ptr)->data[*(*ptr)->size] = malloc(sizeof(**(*ptr)->data));

        (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->type));
        *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_SEPTARR;

        (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(*(*ptr)->data[*(*ptr)->size]->value));
        (*ptr)->data[*(*ptr)->size]->value->septarr_val = value;

        *(*ptr)->size += 1;
        (*ptr)->data[*(*ptr)->size] = NULL;

        return 0;
}

/*
 * The easiest way to get the data that stored in data structure. Make sure
 * that you are not accessing an out-of-bounds value or you will get
 * undefined behavior (UB). Make sure that you use the right function 
 * for the right data type.
 *
 * The reason why I did not make this function safe is
 * because I need speed, so we have to use it carefully.
 * 
 * This comment applied to all septarr_get_*() functions below.
 */
int septarr_get_int(struct septarr *ptr, int index)
{
        return *ptr->data[index]->value->int_val;
}

float septarr_get_float(struct septarr *ptr, int index)
{
        return *ptr->data[index]->value->float_val;
}

double septarr_get_double(struct septarr *ptr, int index)
{
        return *ptr->data[index]->value->double_val;
}

char *septarr_get_string(struct septarr *ptr, int index)
{
        return ptr->data[index]->value->string_val;
}

struct septarr *septarr_get_septarr(struct septarr *ptr, int index)
{
        return ptr->data[index]->value->septarr_val;
}

/*
 * The function that have a responsbility to delete an element of the array
 * inside the data structure.
 */
int septarr_delete_element(struct septarr **ptr, int index)
{
        if (index >= *(*ptr)->size || index < 0)
                return -5;

        int sin = septarr_shrink_if_needed(&(*ptr));

        if (sin < 0)
                return sin;

        switch (*(*ptr)->data[index]->type)
        {
        case SEPTARR_INT:
                free((*ptr)->data[index]->value->int_val);
                break;
        case SEPTARR_FLOAT:
                free((*ptr)->data[index]->value->float_val);
                break;
        case SEPTARR_DOUBLE:
                free((*ptr)->data[index]->value->double_val);
                break;
        case SEPTARR_STRING:
                free((*ptr)->data[index]->value->string_val);
                break;
        case SEPTARR_SEPTARR:
                septarr_destroy(&(*ptr)->data[index]->value->septarr_val);
                break;
        default:
                break;
        }

        free((*ptr)->data[index]->type);
        free((*ptr)->data[index]->value);

        for (int i = index; i < *(*ptr)->size - 1; i++)
                *(*ptr)->data[i] = *(*ptr)->data[i + 1];

        *(*ptr)->size -= 1;

        free((*ptr)->data[*(*ptr)->size]);
        
        (*ptr)->data[*(*ptr)->size] = NULL;

        return 0;
}

/*
 * Destoy the data structure. It will do deallocations for pointers that was allocated
 * during initialization and insertions.
 */
int septarr_destroy(struct septarr **ptr)
{
        for (int i = *(*ptr)->size - 1; i >= 0; i--) {
                switch (*(*ptr)->data[i]->type)
                {
                case SEPTARR_INT:
                        free((*ptr)->data[i]->value->int_val);
                        break;
                case SEPTARR_FLOAT:
                        free((*ptr)->data[i]->value->float_val);
                        break;
                case SEPTARR_DOUBLE:
                        free((*ptr)->data[i]->value->double_val);
                        break;
                case SEPTARR_STRING:
                        free((*ptr)->data[i]->value->string_val);
                        break;
                case SEPTARR_SEPTARR:
                        septarr_destroy(&(*ptr)->data[i]->value->septarr_val);
                        break;
                default:
                        break;
                }

                free((*ptr)->data[i]->type);
                free((*ptr)->data[i]->value);
                free((*ptr)->data[i]);
        }

        free((*ptr)->data);
        free((*ptr)->size);
        free((*ptr)->allocated_size);
        free(*ptr);

        return 0;
}

