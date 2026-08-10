#define MAX_PORT_RETRIES        24
#define VMADDR_CID_NONEXISTING  42

/* Test attempts to trigger a transport release for an unbound
 * socket. This can lead to a reference count mishandling.
 */
static void test_seqpacket_transport_uaf_client(
    const struct test_opts *opts
) {
    int sockets[MAX_PORT_RETRIES];
    struct sockaddr_vm addr;
    int s, i, alen;
    
    s = vsock_bind(
        VMADDR_CID_LOCAL,
        VMADDR_PORT_ANY,
        SOCK_SEQPACKET
    );
    
    alen = sizeof(addr);
    if (getsockname(s, (struct sockaddr *)&addr, &alen)) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < MAX_PORT_RETRIES; ++i) {
        sockets[i] = vsock_bind(
            VMADDR_CID_ANY,
            ++addr.svm_port,
            SOCK_SEQPACKET
        );
    }
    
    close(s);
    s = socket(AF_VSOCK, SOCK_SEQPACKET, 0);
    if (s < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    if (!connect(s, (struct sockaddr *)&addr, alen)) {
        fprintf(stderr, "Unexpected connect() #1 success\n");
        exit(EXIT_FAILURE);
    }
    /* connect() #1 failed: transport set, sk in unbound list. */
    
    addr.svm_cid = VMADDR_CID_NONEXISTING;