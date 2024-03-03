#include "rush02.h"

void read_file(int fd, KeyValuePair **dictionary, int *num_words, int i, long long key) {
    char buffer[BUF_SIZE];
    int bytes_read;
    char value[MAX_WORD_LENGTH];
    int buffer_pos;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) 
    {
        buffer_pos = -1;
        while (++buffer_pos < bytes_read) {
            key = 0;
            i = 0;
            while (buffer[buffer_pos] != ' ' && buffer[buffer_pos] != ':')
                key = key * 10 + (buffer[buffer_pos++] - '0');
            while (buffer[buffer_pos] == ' ' || buffer[buffer_pos] == ':')
                buffer_pos++;
            while (buffer_pos < bytes_read && buffer[buffer_pos] != '\n')
                value[i++] = buffer[buffer_pos++];
            value[i] = '\0';
            (*dictionary)[*num_words].key = key;
            strncpy((*dictionary)[*num_words].value, value, MAX_WORD_LENGTH);
            (*num_words)++;
        }
    }
    fdr(fd, bytes_read);
    close(fd);
}

void affnumber(long long number, KeyValuePair *dictionary, int num_words)
{
    if (number > 0)
    {
        if (number <= 20) 
        {
            putstr(find_value(number, dictionary, num_words));
            putstr(" ");
        }
        else 
        {
            putstr(find_value((number / 10) * 10, dictionary, num_words));
            if (number % 10 != 0) 
            {
                putstr("-");
                putstr(find_value(number % 10, dictionary, num_words));
                putstr(" ");
            }
        }
    }
}

void convert_to_words(unsigned long long number, KeyValuePair *dictionary, int num_words, int start_index) {
    number_null(number);
    unsigned long long units[6];
    int i;

    init_units(units);
    i = index_start(start_index, number) - 1;
    while (++i < 6) 
    {
        if (number >= units[i]) 
        {
            convert_to_words(number / units[i], dictionary, num_words, start_index);
            putstr(find_value(units[i], dictionary, num_words));
            putstr(" ");
            number %= units[i];
        }
    }
    if (number >= 100) 
    {
        convert_to_words(number / 100, dictionary, num_words, start_index);
        putstr(find_value(100, dictionary, num_words));
        putstr(" ");
        number %= 100;
        if (number != 0) 
            putstr("and ");
    }
    affnumber(number,  dictionary, num_words);
}

void read_dictionary(char *filename, KeyValuePair **dictionary, int *num_words) {
    int fd;
    fd = open_file(filename);
    read_file(fd, dictionary, num_words, 0 , 0);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) 
    {
        putstr(argv[0]);
        putstr(" dictionary | number\n");
        return EXIT_FAILURE;
    }
    KeyValuePair *dictionary;
    dictionary = malloc(MAX_WORD_LENGTH * sizeof(KeyValuePair));
    if (dictionary == NULL) 
    {
        write(1,"Memory allocation failed", strlen("Memory allocation failed"));
        return EXIT_FAILURE;
    }
    int num_words;
    num_words = 0;
    if (argc == 3) 
        read_dictionary(argv[1], &dictionary, &num_words);
    else 
        read_dictionary("numbers.dict", &dictionary, &num_words);
    long long number = ft_atoi(argv[argc - 1]);
    convert_to_words(number, dictionary, num_words, 0);
    putstr("\n");
    free(dictionary);
    return EXIT_SUCCESS;
}
