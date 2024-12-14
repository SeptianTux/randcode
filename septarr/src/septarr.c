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

    (*ptr)->data[*(*ptr)->size] = malloc(sizeof(struct SEPTARR_DATA));

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(int));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_INT;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(int));
    *((int *)(*ptr)->data[*(*ptr)->size]->value) = value;

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

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(int));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_FLOAT;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(float));
    *(float *)(*ptr)->data[*(*ptr)->size]->value = value;

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

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(int));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_DOUBLE;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(double));
    *(double *)(*ptr)->data[*(*ptr)->size]->value = value;

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

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(int));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_STRING;

    (*ptr)->data[*(*ptr)->size]->value = malloc(sizeof(char)*strlen(value)+1);
    strcpy((char *)(*ptr)->data[*(*ptr)->size]->value, value);

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

    (*ptr)->data[*(*ptr)->size]->type = malloc(sizeof(int));
    *(*ptr)->data[*(*ptr)->size]->type = SEPTARR_SEPTARR;

    (*ptr)->data[*(*ptr)->size]->value = value;

    *(*ptr)->size = *(*ptr)->size+1;
    (*ptr)->data[*(*ptr)->size] = NULL;

    return 0;
}

int septarr_get_int(struct SEPTARR *ptr, int index)
{
    return *(int *)ptr->data[index]->value;
}

float septarr_get_float(struct SEPTARR *ptr, int index)
{
    return *(float *)ptr->data[index]->value;
}

double septarr_get_double(struct SEPTARR *ptr, int index)
{
    return *(double *)ptr->data[index]->value;
}

char *septarr_get_string(struct SEPTARR *ptr, int index)
{
    return (char *)ptr->data[index]->value;
}

struct SEPTARR *septarr_get_septarr(struct SEPTARR *ptr, int index)
{
    return (struct SEPTARR *)ptr->data[index]->value;
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

    if(*(*ptr)->data[index]->type == SEPTARR_SEPTARR) {
        struct SEPTARR *septarr = (struct SEPTARR *)(*ptr)->data[index]->value;
        septarr_destroy(&septarr);
    } else {
        free((*ptr)->data[index]->value);
    }
    
    free((*ptr)->data[index]->type);

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
        if(*(*ptr)->data[i]->type == SEPTARR_SEPTARR) {
            struct SEPTARR *septarr = (struct SEPTARR *)(*ptr)->data[i]->value;
            septarr_destroy(&septarr);
        } else {
            free((*ptr)->data[i]->value);
        }
        
        free((*ptr)->data[i]->type);
        free((*ptr)->data[i]);
    }

    free((*ptr)->data);
    free((*ptr)->size);
    free((*ptr)->allocated_size);
    free(*ptr);

    return 0;
}

