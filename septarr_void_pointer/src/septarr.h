#define SEPTARR_INIT_SIZE   2048

enum SEPTARR_TYPE
{
    SEPTARR_INT,
    SEPTARR_FLOAT,
    SEPTARR_DOUBLE,
    SEPTARR_STRING,
    SEPTARR_SEPTARR
};

struct SEPTARR_DATA
{
    enum SEPTARR_TYPE *type;
    void *value;
};

struct SEPTARR
{
    int *size;
    int *allocated_size;
    struct SEPTARR_DATA **data;
};

struct SEPTARR *septarr_init();
int septarr_get_size(struct SEPTARR *ptr);
int septarr_get_allocated_size(struct SEPTARR *ptr);
int septarr_get_type(struct SEPTARR *ptr, int index);
int septarr_push_int(struct SEPTARR **ptr, int value);
int septarr_push_float(struct SEPTARR **ptr, float value);
int septarr_push_double(struct SEPTARR **ptr, double value);
int septarr_push_string(struct SEPTARR **ptr, char *value);
int septarr_push_septarr(struct SEPTARR **ptr, struct SEPTARR *value);
int septarr_get_int(struct SEPTARR *ptr, int index);
float septarr_get_float(struct SEPTARR *ptr, int index);
double septarr_get_double(struct SEPTARR *ptr, int index);
char *septarr_get_string(struct SEPTARR *ptr, int index);
struct SEPTARR *septarr_get_septarr(struct SEPTARR *ptr, int index);
int septarr_delete_element(struct SEPTARR **ptr, int index);
int septarr_destroy(struct SEPTARR **ptr);