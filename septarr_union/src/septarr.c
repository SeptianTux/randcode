#include "septarr.h"
#include <stdlib.h>
#include <string.h>

struct SEPTARR *septarr_init()
{
    struct SEPTARR *ret;

    ret = malloc(sizeof(*ret));
    ret->size = malloc(sizeof(int));
    *ret->size = 0;
    ret->allocated_size = malloc(sizeof(int));
    *ret->allocated_size = SEPTARR_INIT_SIZE;
    ret->data = malloc(sizeof(*ret->data)*SEPTARR_INIT_SIZE);
    ret->data[0] = NULL;

    return ret;
}

int septarr_realloc(struct SEPTARR **ptr, int new_allocated_size)
{
    struct SEPTARR_DATA **new_ptr;
    
    new_ptr = reallocarray((*ptr)->data, new_allocated_size, sizeof(*(*ptr)->data));
    
    if(new_ptr == NULL) {
        return -1;
    }
    
    (*ptr)->data = new_ptr;
    *(*ptr)->allocated_size = new_allocated_size;

    return 0;
}

int septarr_get_size(struct SEPTARR *ptr)
{
    return *ptr->size;
}

int septarr_get_allocated_size(struct SEPTARR *ptr)
{
    return *ptr->allocated_size;
}

int septarr_get_type(struct SEPTARR *ptr, int index)
{
    return *ptr->data[index]->type;
}

int septarr_grow_if_needed(struct SEPTARR **ptr)
{
    if(*(*ptr)->size >= *(*ptr)->allocated_size-1) {
        return septarr_realloc(&(*ptr), *(*ptr)->allocated_size+SEPTARR_INIT_SIZE);
    }

    return 0;
}

int septarr_shrink_if_needed(struct SEPTARR **ptr)
{
    if((*(*ptr)->allocated_size-SEPTARR_INIT_SIZE) >= *(*ptr)->size) {
        return septarr_realloc(&(*ptr), *(*ptr)->allocated_size-SEPTARR_INIT_SIZE);
    }

    return 0;
}

int septarr_push_int(struct SEPTARR **ptr, int value)
{
    int gin = septarr_grow_if_needed(&(*ptr));
    if(gin < 0) {
        return gin;
    }

    (*ptr)->data[*(*ptr)->size] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(enum SEPTARR_TYPE));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_INT;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(union SEPTARR_VALUE));
    (*ptr)->data[*(*ptr)->size]->value->int_val = malloc(sizeof(int));
    *(*ptr)->data[*(*ptr)->size]->value->int_val = value;

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_push_float(struct SEPTARR **ptr, float value)
{
    int gin = septarr_grow_if_needed(&(*ptr));
    if(gin < 0) {
        return gin;
    }

    (*ptr)->data[*(*ptr)->size] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(enum SEPTARR_TYPE));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_FLOAT;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(union SEPTARR_VALUE));
    (*ptr)->data[*(*ptr)->size]->value->float_val = malloc(sizeof(float));
    *(*ptr)->data[*(*ptr)->size]->value->float_val = value;

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_push_double(struct SEPTARR **ptr, double value)
{
    int gin = septarr_grow_if_needed(&(*ptr));
    if(gin < 0) {
        return gin;
    }

    (*ptr)->data[*(*ptr)->size] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(enum SEPTARR_TYPE));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_DOUBLE;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(union SEPTARR_VALUE));
    (*ptr)->data[*(*ptr)->size]->value->double_val = malloc(sizeof(double));
    *(*ptr)->data[*(*ptr)->size]->value->double_val = value;

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_push_string(struct SEPTARR **ptr, char *value)
{
    int gin = septarr_grow_if_needed(&(*ptr));
    if(gin < 0) {
        return gin;
    }

    (*ptr)->data[*(*ptr)->size] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(enum SEPTARR_TYPE));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_STRING;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(union SEPTARR_VALUE));
    (*ptr)->data[*(*ptr)->size]->value->string_val = malloc(sizeof(char)*strlen(value)+1);
    strcpy((*ptr)->data[*(*ptr)->size]->value->string_val, value);

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_push_septarr(struct SEPTARR **ptr, struct SEPTARR *value)
{
    int gin = septarr_grow_if_needed(&(*ptr));
    if(gin < 0) {
        return gin;
    }

    (*ptr)->data[*(*ptr)->size] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(enum SEPTARR_TYPE));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_SEPTARR;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(union SEPTARR_VALUE));
    (*ptr)->data[*(*ptr)->size]->value->septarr_val = value;

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_get_int(struct SEPTARR *ptr, int index)
{
    return *ptr->data[index]->value->int_val;
}

float septarr_get_float(struct SEPTARR *ptr, int index)
{
    return *ptr->data[index]->value->float_val;
}

double septarr_get_double(struct SEPTARR *ptr, int index)
{
    return *ptr->data[index]->value->double_val;
}

char *septarr_get_string(struct SEPTARR *ptr, int index)
{
    return ptr->data[index]->value->string_val;
}

struct SEPTARR *septarr_get_septarr(struct SEPTARR *ptr, int index)
{
    return ptr->data[index]->value->septarr_val;
}

int septarr_delete_element(struct SEPTARR **ptr, int index)
{
    if(index >= *(*ptr)->size) {
        return -5;
    }

    int sin = septarr_shrink_if_needed(&(*ptr));
    if(sin < 0) {
        return sin;
    }

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

    for(int i=index; i<*(*ptr)->size-1; i++) {
        *(*ptr)->data[i] = *(*ptr)->data[i+1];
    }

    *(*ptr)->size = *(*ptr)->size-1;

    free((*ptr)->data[*(*ptr)->size]);
    
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_destroy(struct SEPTARR **ptr)
{
    for(int i=*(*ptr)->size-1; i>=0; i--) {
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

