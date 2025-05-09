#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "lock.h"
#include "record.h"


void lock_record(int fd, int rec_no) {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = rec_no * sizeof(struct record_s);
    lock.l_len = sizeof(struct record_s);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Cannot lock record");
        exit(1);
    }
}

void unlock_record(int fd, int rec_no) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = rec_no * sizeof(struct record_s);
    lock.l_len = sizeof(struct record_s);

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Cannot unlock record");
        exit(1);
    }
}
