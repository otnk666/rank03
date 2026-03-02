#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int check_int(int ac, char **av)
{
    int i = 1;

    while(i < ac)
    {
        int j = 0;
        if(av[i][j] == '-' || av[i][j] == '+')
            j++;
        while(av[i][j])
        {
            if(av[i][j] < '0' || av[i][j] > '9')
                return(0);
            j++;
        }
        i++;
    }
    return 1;
}

void solve(int *nums, int size, int target, int *subset, int index, int sub_size, int curr_sum)
{
    if(index == size)
    {
        
    }


}

int main(int ac, char **av)
{
    if (ac >= 3 && check_int(ac,av))
    {
        int target = atoi(av[1]);
        int *nums = (int *)malloc(sizeof(int) * (ac - 2));
        for (int i = 0; i < ac - 2; i++)
        {
            nums[i] = atoi(av[i + 2]);
        }
        int subset[ac - 2];
        solve(nums, ac - 2, target, subset, 0, 0, 0);
    }

    
    return 1;
    
}