#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "record.h"
#include "lock.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Cannot open file");
        exit(1);
    }

    int choice, rec_no;
    struct record_s rec, rec_wrk, rec_new;

    while (1) {
        printf("Menu:\n");
        printf("1. List records\n");
        printf("2. Get record\n");
        printf("3. Modify record\n");
        printf("4. Create record\n");
        printf("0. Exit\n");
        printf("Select choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_records(fd);
                break;
            case 2:
                printf("Enter record number: ");
                scanf("%d", &rec_no);
                get_record(fd, rec_no);
                break;
            case 3:
                printf("Enter record number to modify: ");
                scanf("%d", &rec_no);

                lseek(fd, rec_no * sizeof(struct record_s), SEEK_SET);
                if (read(fd, &rec, sizeof(struct record_s)) <= 0) {
                    printf("Record not found\n");
                    continue;
                }

                rec_wrk = rec;
                modify_record(&rec_wrk);

                if (check_record_changed(&rec, &rec_wrk)) {
                    lock_record(fd, rec_no);

                    lseek(fd, rec_no * sizeof(struct record_s), SEEK_SET);
                    read(fd, &rec_new, sizeof(struct record_s));

                    if (check_record_changed(&rec, &rec_new)) {
                        unlock_record(fd, rec_no);
                        printf("Record was modified by another process!\n");
                        rec = rec_new;
                        continue;
                    }

                    put_record(fd, rec_no, &rec_wrk);
                    unlock_record(fd, rec_no);
                }
                break;
            case 4:
                create_record(fd);
                break;
            case 0:
                close(fd);
                return 0;
            default:
                printf("Invalid command\n");
        }
    }
}
