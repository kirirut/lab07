#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "record.h"

void create_record(int fd) {
    struct record_s rec;
    printf("Enter name: ");
    scanf(" %[^\n]", rec.name);
    printf("Enter address: ");
    scanf(" %[^\n]", rec.address);
    printf("Enter semester: ");
    scanf("%hhu", &rec.semester);
    
    lseek(fd, 0, SEEK_END);
    write(fd, &rec, sizeof(struct record_s));
    printf("Record created successfully\n");
}

void list_records(int fd) {
    struct record_s rec;
    int i = 0;
    
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &rec, sizeof(struct record_s)) > 0) {
        printf("Record %d:\n", i++);
        printf("Name: %s\n", rec.name);
        printf("Address: %s\n", rec.address);
        printf("Semester: %d\n", rec.semester);
        printf("------------------\n");
    }
}

void get_record(int fd, int rec_no) {
    struct record_s rec;
    
    lseek(fd, rec_no * sizeof(struct record_s), SEEK_SET);
    if (read(fd, &rec, sizeof(struct record_s)) > 0) {
        printf("Record %d:\n", rec_no);
        printf("Name: %s\n", rec.name);
        printf("Address: %s\n", rec.address);
        printf("Semester: %d\n", rec.semester);
    } else {
        printf("Record not found\n");
    }
}

void modify_record(struct record_s *rec) {
    char input[80];
    printf("Enter new name (or press Enter to keep old): ");
    scanf(" %[^\n]", input);
    if (strlen(input) > 0) {
        strncpy(rec->name, input, 80);
    }

    printf("Enter new address (or press Enter to keep old): ");
    scanf(" %[^\n]", input);
    if (strlen(input) > 0) {
        strncpy(rec->address, input, 80);
    }

    printf("Enter new semester (or press Enter to keep old): ");
    scanf(" %[^\n]", input);
    if (strlen(input) > 0) {
        rec->semester = atoi(input);
    }
}

void put_record(int fd, int rec_no, struct record_s *rec) {
    lseek(fd, rec_no * sizeof(struct record_s), SEEK_SET);
    write(fd, rec, sizeof(struct record_s));
    printf("Record saved successfully\n");
}

int check_record_changed(struct record_s *rec1, struct record_s *rec2) {
    return strcmp(rec1->name, rec2->name) != 0 ||
           strcmp(rec1->address, rec2->address) != 0 ||
           rec1->semester != rec2->semester;
}
