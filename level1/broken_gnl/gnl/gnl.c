#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *ft_strdup(const char *str)
{
    char *copy;
    int i;
    int len = 0;
    
    while (str[len])
        len++;
    
    copy = (char *)malloc(sizeof(char) * (len + 1));
    if (copy == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0')
    {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    char line[70000];
    static int b_read;
    static int b_pos;
    int i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    while (1)  // 1337 → 1 に変更
    {
        if (b_pos >= b_read)
        {
            b_read = read(fd, buffer, BUFFER_SIZE);
            b_pos = 0;
            if (b_read <= 0)
                break;
        }
        line[i++] = buffer[b_pos++];
        if (line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}

#include <fcntl.h>
int main(){
    int fd = open("file.txt", O_RDWR);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
}