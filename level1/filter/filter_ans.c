#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    char *input_buffer;
    char *temp_buffer;
    char *search_str;
    ssize_t read_size;
    size_t search_len;
    size_t total_size;
    
    if (argc != 2 || !argv[1][0])
        return (1);

    input_buffer = NULL;
    search_str = argv[1];
    search_len = strlen(search_str);
    total_size = 0;

    while(1)
    {
        temp_buffer = realloc(input_buffer, total_size + BUFFER_SIZE);
        if(!temp_buffer)
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
        
        total_size = read_size + total_size;
    }

    char *current = input_buffer;
    size_t remaining = total_size;
    char *match;
    size_t i = 0;
    size_t j = 0;

    while (remaining > 0)
    {
        match = memmem(current, remaining, search_str, search_len);
        
        if (!match)
        {
            printf("%s", current);
            break;
        }

        size_t before_len = match - current;
        while (i < before_len)
        {
            printf("%c", current[i]);
            i++;
        }
        i = 0;
        while (j < search_len)
        {
            printf("*");
            j++;
        }
        j = 0;
        remaining = remaining - before_len - search_len;
        current = match + search_len;
    }
    free(input_buffer);
    return (0);
}