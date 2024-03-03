#include "rush02.h"

void putstr(char *str) 
{
    if (str != NULL)
        write(1, str, strlen(str));
}

char *find_value(long long key, KeyValuePair *dictionary, int num_words) 
{
    int i = 0;
    while (i < num_words) 
    {
        if (dictionary[i].key == key) 
            return dictionary[i].value;
        i++;
    }
    return NULL;
}

int index_start(int start_index, long long number)
{
       if (number >= 1000000000000000000LL)
        start_index = 0; // sextillion
    else if (number >= 1000000000000000LL)
        start_index = 1; // quintillion
    else if (number >= 1000000000000LL)
        start_index = 2; // quadrillion
    else if (number >= 1000000000)
        start_index = 3; // trillion
    else if (number >= 1000000)
        start_index = 4; // billion
    else if (number >= 1000)
        start_index = 5; // million
    return start_index;
}