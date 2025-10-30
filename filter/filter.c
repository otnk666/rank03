#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096


int main(int argc, char **argv)
{
    char *pattern;
    size_t pattern_len;
    char *read_buffer;
    char *overlap_buffer;
    size_t overlap_size;
    char *work_buffer;
    size_t work_size;
    ssize_t bytes_read;
    size_t safe_size;

    if (argc != 2)
        return (1);
    
    pattern = argv[1];
    pattern_len = str
    
}