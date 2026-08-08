void uaf_example(void) {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 5;

    free(ptr);        // ptr is now a dangling pointer

    *ptr = 10;        // use-after-free: access to freed memory

    ptr = NULL;
}