

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "file.h"

int create_db_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd != STATUS_ERROR)
    {
        printf("File %s already exists!\n", filepath);
        close(fd);
        return STATUS_ERROR;
    }

    fd = open(filepath, O_RDWR | O_CREAT, 0644);
    if (fd == STATUS_ERROR)
    {
        perror("create_database_file");
        return STATUS_ERROR;
    }
    return fd;
}

int read_db_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd == STATUS_ERROR)
    {
        perror("read_database_file");
        return STATUS_ERROR;
    }
    return fd;
}