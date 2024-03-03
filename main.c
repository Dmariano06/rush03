#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100
#define BUF_SIZE 4096

// structure pour stocker  la clé valeur du dictionnaire
typedef struct {
    long long key;
    char value[MAX_WORD_LENGTH];
} KeyValuePair;

long long ft_atoi(char *str)
{
        long long res = 0;
        int sign = 1;
        int i;

        i = 0;
        while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        {
                i++;
        }
        while(str[i] == '+' || str[i] == '-')
        {
                if(str[i] == '-')
                        sign *= -1;
                i++;
        }

        while(str[i] >= '0' && str[i] <= '9')
        {
                res *= 10;
                res += str[i] - '0';
                i++;
        }
        return sign * res;

}

// F() pour lire le fichier .dict et fill le tab la clé valeur
void read_dictionary(char *filename, KeyValuePair *dictionary, int *num_words) {
    int fd = open(filename, O_RDONLY); // open file READONLY
    if (fd == -1) {
        write(2, "Dict Error\n", strlen("Dict Error\n"));
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];  //char pour stocker les donnés lues depuis le fichier
    int bytes_read;
     // lire le file par block
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        int buffer_pos = 0;
        while (buffer_pos < bytes_read && *num_words < MAX_WORDS) 
        {
               long long key = 0;          // key from file
            char value[MAX_WORD_LENGTH] = {'\0'};   // value from file
            int i = 0;              
            while (buffer[buffer_pos] != ' ' && buffer[buffer_pos] != ':') 
            {
                key = key * 10 + (buffer[buffer_pos] - '0');   // extract key
                buffer_pos++;
            }
            while (buffer[buffer_pos] == ' ' || buffer[buffer_pos] == ':') 
            {
                buffer_pos++;
            }
            while (buffer_pos < bytes_read && buffer[buffer_pos] != '\n') 
            {
                value[i++] = buffer[buffer_pos++];  // extract la value
            }
            dictionary[*num_words].key = key;
            strncpy(dictionary[*num_words].value, value, MAX_WORD_LENGTH);
            (*num_words)++;
            while (buffer_pos < bytes_read && buffer[buffer_pos] == '\n') {
                buffer_pos++;
            }
        }
    }

    if (bytes_read == -1) 
    {
        write(2, "Dict Error\n", strlen("Dict Error\n"));
        exit(EXIT_FAILURE);
    }

    close(fd);
}

char *find_value(long long key, KeyValuePair *dictionary, int num_words) 
{
    
int i = 0;
while (i < num_words) 
{
    if (dictionary[i].key == key) 
    {
        return dictionary[i].value;
    }
    i++;
}
    return NULL;
}

void putstr(char *str) 
{
    if (str != NULL) { 
        write(1, str, strlen(str));
    }
}

void convert_to_words(long long number, KeyValuePair *dictionary, int num_words) 
{
    if (number == 0) {
        putstr("zero\n");
        return;
    }
    if (number < 0) {
        putstr("minus ");
        number = -number;
    }
    long long units[] = {1000000000000000000LL,
                         1000000000000000LL,
                         1000000000000LL,
                         1000000000,
                         1000000,
                         1000};
    int start_index = 0;
    if (number >= 1000000000000000000LL) {
        start_index = 0; // sextillion
    } else if (number >= 1000000000000000LL) {
        start_index = 1; // quintillion
    } else if (number >= 1000000000000LL) {
        start_index = 2; // quadrillion
    } else if (number >= 1000000000) {
        start_index = 3; // trillion
    } else if (number >= 1000000) {
        start_index = 4; // billion
    } else if (number >= 1000) {
        start_index = 5; // million
    }
    int i = start_index;
    while(i < 6)
    {
    if (number >= units[i]) 
    {
            convert_to_words(number / units[i], dictionary, num_words);
            putstr(find_value(units[i], dictionary, num_words));
            putstr(" ");
            number %= units[i];
    }
        ++i;
    }
    if (number >= 100) 
    {
        convert_to_words(number / 100, dictionary, num_words);
        putstr(find_value(100, dictionary, num_words));
        putstr(" ");
        number %= 100;
        if (number != 0) 
        {
            putstr("and ");
        }
    }
    if (number > 0) 
    {
        if (number < 20) 
        {
            putstr(find_value(number, dictionary, num_words));
        } else 
        {
            putstr(find_value((number / 10) * 10, dictionary, num_words));
            if (number % 10 != 0) 
            {
                putstr("-");
                putstr(find_value(number % 10, dictionary, num_words));
            }
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2 || argc > 3) 
    {
        putstr("Usage: ");
        putstr(argv[0]);
        putstr(" dictionary number\n");
        return EXIT_FAILURE;
    }

    KeyValuePair dictionary[MAX_WORDS];
    int num_words = 0;

    if (argc == 3) 
    {
        read_dictionary(argv[1], dictionary, &num_words);
    } else 
    {
        read_dictionary("numbers.dict", dictionary, &num_words);
    }

    long long number = ft_atoi(argv[argc - 1]);

    convert_to_words(number, dictionary, num_words);

    putstr("\n");

    return EXIT_SUCCESS;
}
