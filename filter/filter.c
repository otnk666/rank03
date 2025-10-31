#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096


int process_and_write(char *data, size_t data_size, char *pattern, size_t pattern_len, size_t safe_size)
{
    char 
}

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
    pattern_len = strlen(pattern);
    
    if (pattern_len == 0)
        return (1);

    read_buffer = malloc(BUFFER_SIZE);
    if (!read_buffer)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return (1);
    }

    overlap_buffer = malloc(pattern_len - 1);
    if (!overlap_buffer)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        free(read_buffer);
        return (1);
    }
    work_buffer = malloc(BUFFER_SIZE + pattern_len - 1);
    if (!work_buffer)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        free(overlap_buffer);
        free(read_buffer);
        return (1);
    }

    overlap_size = 0;

    while (1)
    {
        bytes_read = read(STDIN_FILENO, read_buffer, BUFFER_SIZE);

        if (bytes_read < 0)
        {
            perror("Error");
            free(work_buffer);
            free(overlap_buffer);
            free(read_buffer);
            return (1);
        }

        if (bytes_read == 0)
            break;
        
        if (overlap_size > 0)
            memmove(work_buffer, overlap_buffer, overlap_size);
        memmove(work_buffer + overlap_size, read_buffer, bytes_read);
        work_size = overlap_size + bytes_read;

        if (work_size >= pattern_len)
            safe_size = work_size - (pattern_len - 1);
        else
            safe_size = 0;

        if (safe_size > 0)
        {
            if (process_and_write(work_buffer, work_size, pattern, pattern_len, safe_size) < 0)
            {
                perror("Error");
                free(work_buffer);
                free(overlap_buffer);
                free(read_buffer);
                return (1);
            }
        }

        overlap_size = work_size = safe_size;
        if (overlap_size > 0)
            memmove(overlap_buffer, work_buffer + safe_size, overlap_size);
    }
    if (overlap_size > 0)
    {
        if (wirte(STDOUT_FILENO, overlap_buffer, overlap_size))
        {
            perror("Error");
            free(work_buffer);
            free(overlap_buffer);
            free(read_buffer);
            return (1);
        }
    }
    free(work_buffer);
    free(overlap_buffer);
    free(read_buffer);

    return(0);
}