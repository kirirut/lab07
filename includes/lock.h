#ifndef LOCK_H
#define LOCK_H

void lock_record(int fd, int rec_no);
void unlock_record(int fd, int rec_no);

#endif
