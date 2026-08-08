void reference_count_example(void) {
    int *ptr = malloc(sizeof(int));
    int ref_count = 1;       // starting with 1 existing reference

    ref_count++;             // new reference
    ref_count--;             // release of a reference
    ref_count--;             // release of the last reference

    if (ref_count == 0)
        free(ptr);
}