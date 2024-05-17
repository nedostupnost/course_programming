#ifndef WORDS_COUNT_H
#define WORDS_COUNT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 256
#define HASH_TABLE_SIZE 4096

// Структура списка, представляющая слово и его частоту
typedef struct nodelist {
  char key[MAX_WORD_LENGTH];
  int value;
  struct nodelist *next;
} nodelist;

extern nodelist *hashTable[HASH_TABLE_SIZE]; // Хеш-таблица для хранения слов

// Прототипы функций
unsigned int hash(const char *str);
void add_word(const char *key);
void print_frequencies(nodelist *head, FILE *f);
void sort_table(nodelist **head);
char *rm_punct(const char *key);

#endif