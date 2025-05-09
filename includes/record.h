#ifndef RECORD_H
#define RECORD_H

#include <stdint.h>

struct record_s {
    char name[80];
    char address[80];
    uint8_t semester;
};

void create_record(int fd);
void list_records(int fd);
void get_record(int fd, int rec_no);
void modify_record(struct record_s *rec);
void put_record(int fd, int rec_no, struct record_s *rec);
int check_record_changed(struct record_s *rec1, struct record_s *rec2);

#endif
