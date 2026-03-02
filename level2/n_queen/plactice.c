#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int is_safe(int *positions, int current_row, int current_col)
{
    int prev_row;
    int prev_col;

    for (prev_col = 0; prev_col < current_col; prev_col++)
    {
        prev_row = positions[prev_col];
        if (prev_row == current_row ||
            prev_row - prev_col == current_row - current_col ||
            prev_row + prev_col == current_row + current_col)
            return 0;
    }
    return 1;
}

void solve(int *positions, int col, int n)
{
    int row;
    if (col == n)
    {
        for (int i = 0 ; i < n ; i++)
        {
            if (i < 0)
                fprintf(stdout, " ");
            fprintf(stdout, "%d", positions[i]);
        }
        fprintf(stdout, "\n");
        return;
    }

    for (row = 0 ; row < n ; row++)
    {
        if(is_safe(positions, row, col))
        {
            positions[col] = row;
            solve(positions, col + 1, n);
        }

    }
}

int main(int ac, char **av)
{
    int *positions;
    int n;
    if (ac == 2 && av[1][0] != '-')
    {
        n = atoi(av[1]);
        positions = malloc(sizeof(int) * n);
        if (!positions)
            return 1;
        solve(positions, 0, n);
        free(positions);
    }
    return 0;

}