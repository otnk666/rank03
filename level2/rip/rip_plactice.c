#include <stdio.h>

int is_val(char *str)
{
    int opened = 0;
    int closed = 0;

    int i = 0;
    while (str[i])
    {
        if (str[i] =='(')
            opened++;
        else if(str[i] == ')')
        {
            if(opened > 0)
                opened--;
            else
                closed++;
        }
        i++;
    }
    return (opened+closed);
}

void rip(char *str, int must_fix, int n_fix, int pos)
{
    if (must_fix == n_fix && !is_val(str))
    {
        puts(str);
        return;
    }

    for (int i = pos; str[i]; i++)
    {
        if (str[i] == '(' || str[i] == ')')
        {
            int c = str[i];
            str[i] = ' ';
            rip(str, must_fix, n_fix + 1, i);
            str[i] = c;
        }
    }
}

int main(int ac, char **av)
{
    int m_fix = is_val(av[1]);
    rip(av[1], m_fix, 0, 0);
}