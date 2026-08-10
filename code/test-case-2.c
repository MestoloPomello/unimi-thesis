    if (!connect(s, (struct sockaddr *)&addr, alen)) {
        fprintf(stderr, "Unexpected connect() #2 success\n");
        exit(EXIT_FAILURE);
    }
    /* connect() #2 failed: transport unset, sk ref dropped? */

    addr.svm_cid = VMADDR_CID_LOCAL;
    addr.svm_port = VMADDR_PORT_ANY;
    
    /* Vulnerable system may crash now. */
    bind(s, (struct sockaddr *)&addr, alen);
    
    close(s);
    while (i--)
        close(sockets[i]);
        
    control_writeln("DONE");
}