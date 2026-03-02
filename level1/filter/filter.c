#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int ac, char **av)
{
    char *pattern;
    size_t pattern_len;
    char *input_buffer;
    char *temp_buffer;
    ssize_t read_size;
    size_t total_size;
    char *match;
    size_t remaining;

    if (ac != 2)
        return (1);
    
    pattern = av[1];
    pattern_len = strlen(pattern);
    input_buffer = NULL;
    total_size = 0;
    while(1)
    {
        temp_buffer = realloc(input_buffer, total_size + BUFFER_SIZE);
        if (!temp_buffer)
        {
            perror("Error");
            free(input_buffer);
            return (1);
        }

        input_buffer = temp_buffer;
        read_size = read(STDIN_FILENO, input_buffer + total_size, BUFFER_SIZE);
        if (read_size < 0)
        {
            perror("Error");
            free(input_buffer);
            return (1);
        }
        if (read_size == 0)
            break;
        total_size += read_size; 
    }

    char *current;
    size_t before_len;
    size_t i = 0;
    size_t j = 0;

    current = input_buffer;
    remaining = total_size;
    
    while(remaining > 0)
    {
        match = memmem(current, remaining, pattern, pattern_len);
        if (!match)
        {
            printf("%s", current);
            break;
        }
        before_len = match - current;
        
        while(i < before_len)
        {
            printf("%c", current[i]);
            i++;
        }
        i = 0;

        while(j < pattern_len)
        {
            printf("*");
            j++;
        }
        j = 0;
    
        remaining -= before_len - pattern_len;
        current = match + pattern_len;
    }
    free(input_buffer);
    return (0);
}