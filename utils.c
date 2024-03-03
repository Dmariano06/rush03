#include "rush02.h"

long long ft_atoi(char *str) {
    long long res;
    int sign;
    int i;

    i = 0;
    res = 0;
    sign = 1;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) 
    {
        i++;
    }
    while (str[i] == '+' || str[i] == '-') 
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') 
    {
        res *= 10;
        res += str[i] - '0';
        i++;
    }
    return sign * res;
}

void number_null(int number)
{
     if (number == 0)
    {
        putstr("zero\n");
        return;
    }
}

void init_units(unsigned long long units[6]) {
    units[0] = 1000000000000000000LL;
    units[1] = 1000000000000000LL;
    units[2] = 1000000000000LL;
    units[3] = 1000000000;
    units[4] = 1000000;
    units[5] = 1000;
}

int open_file(char *filename) {
    int fd = open(filename, O_RDONLY);
    fdr(fd, 0);
    return fd;
}

void fdr(int fd, int bytes_read)
{    
    if (fd == -1)
    {
        write(2, "Dict Error\n", strlen("Dict Error\n"));
        exit(EXIT_FAILURE);
    }

    if (bytes_read == -1)
    {
        write(2, "Dict Error\n", strlen("Dict Error\n"));
        exit(EXIT_FAILURE);
    }
}