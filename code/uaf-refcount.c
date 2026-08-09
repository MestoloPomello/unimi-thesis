typedef struct {
    int value;
    int refcount;
} Object;

void uaf_refcount(void) {
    Object *obj = malloc(sizeof(Object));
    obj->value = 5;
    obj->refcount = 1;

    Object *ptr = obj;       // new reference
    /* BUG: missing obj->refcount++ */

    if (--obj->refcount == 0)
        free(obj);           // obj is freed early

    int value = ptr->value;  // use-after-free
}