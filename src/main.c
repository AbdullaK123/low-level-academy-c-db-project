#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "file.h"
#include "common.h"
#include "parse.h"

void print_usage(char *argv[])
{
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\t -n = create new database file\n");
    printf("\t -f = required path to database file\n");
}

int main(int argc, char *argv[])
{
    int c;
    bool newFile = false;
    char *filePath = NULL;
    struct dbheader_t *header = NULL;

    while ((c = getopt(argc, argv, "nf:")) != -1)
    {
        switch (c)
        {
        case 'n':
            newFile = true;
            break;
        case 'f':
            filePath = optarg;
            break;
        case '?':
            printf("Unknown option: -%c\n", c);
            break;
        default:
            return -1;
        }
    }

    if (filePath == NULL)
    {
        printf("File path -f is a required argument!\n");
        print_usage(argv);
        return -1;
    }

    int fd;
    if (newFile)
    {
        fd = create_db_file(filePath);
        if (create_db_header(fd, &header) == STATUS_ERROR)
        {
            printf("Failed to create database header\n");
            return -1;
        }
    }
    else
    {
        fd = read_db_file(filePath);
        if (validate_db_header(fd, &header) == STATUS_ERROR)
        {
            printf("Failed to validate database header\n");
            return -1;
        }
    }

    if (fd == -1)
    {
        printf("Failed to open database: %s\n", filePath);
        return -1;
    }

    printf("New file: %d\n", newFile);
    printf("Filepath: %s\n", filePath);

    output_file(fd, header);

    close(fd);
    return 0;
}