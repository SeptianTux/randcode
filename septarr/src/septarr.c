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

    int index;
    if(*(*ptr)->size == 0) {
        index = 0;
    } else if(*(*ptr)->size >= 0) {
        index = *(*ptr)->size;
    }

    (*ptr)->data[index] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[index]->type = malloc(sizeof(int));
    *(*ptr)->data[index]->type = SEPTARR_INT;

    (*ptr)->data[index]->value = malloc(sizeof(int));
    *((int *)(*ptr)->data[index]->value) = value;

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

    int index;
    if(*(*ptr)->size == 0) {
        index = 0;
    } else if(*(*ptr)->size >= 0) {
        index = *(*ptr)->size;
    }

    (*ptr)->data[index] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[index]->type = malloc(sizeof(int));
    *(*ptr)->data[index]->type = SEPTARR_FLOAT;

    (*ptr)->data[index]->value = malloc(sizeof(float));
    *(float *)(*ptr)->data[index]->value = value;

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

    int index;
    if(*(*ptr)->size == 0) {
        index = 0;
    } else if(*(*ptr)->size >= 0) {
        index = *(*ptr)->size;
    }

    (*ptr)->data[index] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[index]->type = malloc(sizeof(int));
    *(*ptr)->data[index]->type = SEPTARR_DOUBLE;

    (*ptr)->data[index]->value = malloc(sizeof(double));
    *(double *)(*ptr)->data[index]->value = value;

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

    int index;
    if(*(*ptr)->size == 0) {
        index = 0;
    } else if(*(*ptr)->size >= 0) {
        index = *(*ptr)->size;
    }

    (*ptr)->data[index] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[index]->type = malloc(sizeof(int));
    *(*ptr)->data[index]->type = SEPTARR_STRING;

    (*ptr)->data[index]->value = malloc(sizeof(char)*strlen(value)+1);
    strcpy((char *)(*ptr)->data[index]->value, value);

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_get_int(struct SEPTARR **ptr, int index)
{
    return *(int *)(*ptr)->data[index]->value;
}

float septarr_get_float(struct SEPTARR **ptr, int index)
{
    return *(float *)(*ptr)->data[index]->value;
}

double septarr_get_double(struct SEPTARR **ptr, int index)
{
    return *(double *)(*ptr)->data[index]->value;
}

char *septarr_get_string(struct SEPTARR **ptr, int index)
{
    return (char *)(*ptr)->data[index]->value;
}

int septarr_delete_element(struct SEPTARR **ptr, int index)
{
    if(index >= *(*ptr)->size) {
        return -1;
    }

    int sin = septarr_shrink_if_needed(&(*ptr));
    if(sin < 0) {
        return sin;
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

