#define SEPTARR_INT         0
#define SEPTARR_FLOAT       1
#define SEPTARR_DOUBLE      2
#define SEPTARR_STRING      3

#define SEPTARR_INIT_SIZE   2048

struct SEPTARR_DATA
{
    int *type;
    void *value;
};

struct SEPTARR
{
    int *size;
    int *allocated_size;
    struct SEPTARR_DATA **data;
};

struct SEPTARR *septarr_init();
int septarr_realloc(struct SEPTARR **ptr, int new_allocated_size);
int septarr_get_size(struct SEPTARR *ptr);
int septarr_get_allocated_size(struct SEPTARR *ptr);
int septarr_grow_if_needed(struct SEPTARR **ptr);
int septarr_shrink_if_needed(struct SEPTARR **ptr);
int septarr_push_int(struct SEPTARR **ptr, int value);
int septarr_push_float(struct SEPTARR **ptr, float value);
int septarr_push_double(struct SEPTARR **ptr, double value);
int septarr_push_string(struct SEPTARR **ptr, char *value);
int septarr_get_int(struct SEPTARR **ptr, int index);
float septarr_get_float(struct SEPTARR **ptr, int index);
double septarr_get_double(struct SEPTARR **ptr, int index);
char *septarr_get_string(struct SEPTARR **ptr, int index);
int septarr_delete_element(struct SEPTARR **ptr, int index);
int septarr_destroy(struct SEPTARR **ptr);