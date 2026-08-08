void dangling_pointer_example(void){
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 5;
    free(ptr); // ptr is now a dangling pointer
    ptr = NULL; // now it doesn't point to the freed zone anymore
}