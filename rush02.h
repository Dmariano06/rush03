#ifndef RUSH02_H
#define RUSH02_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define BUF_SIZE 4096

typedef struct {
    long long key;
    char value[MAX_WORD_LENGTH];
} KeyValuePair;

void affnumber(long long number, KeyValuePair *dictionary, int num_words);
long long ft_atoi(char *str);
int index_start(int start_index, long long number);
char *find_value(long long key, KeyValuePair *dictionary, int num_words);
void putstr(char *str);
void fdr(int fd, int bytes_read);
int open_file(char *filename);
void init_units(unsigned long long units[6]);
void number_null(int number);
#endif