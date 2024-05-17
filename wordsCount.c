#include "wordsCount.h"

nodelist *hashTable[HASH_TABLE_SIZE] = {0};

// Функция генерации хеша для слова
unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_TABLE_SIZE;
}

// Удаляем знак препинания в слове
char* rm_punct(const char* key) {
    int len = strlen(key);
    char* new_key = malloc(len + 1); 
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (key[i] == ',' || key[i] == '.' || key[i] == '!' || key[i] == '?' || key[i] == ':' || key[i] == ';' || key[i] == '(' || key[i] == ')' || key[i] == '-' || key[i] == '"') {
            new_key[j++] = ' ';
        } else {
            new_key[j++] = key[i];
        }
    }
    new_key[j] = '\0';

    return new_key;
}


// Функция добавления слова в хеш-таблицу или обновления его частоты
void add_word(const char *key) {
    char* key_no_punct = rm_punct(key);
    unsigned int index = hash(key_no_punct);
    nodelist *wc = hashTable[index];

    while (wc != NULL) {
        if (strcmp(wc->key, key_no_punct) == 0) {
            wc->value++;
            free(key_no_punct);
            return;
        }
        wc = wc->next;
    }

    wc = (nodelist*) malloc(sizeof(nodelist));
    strcpy(wc->key, key_no_punct);
    wc->value = 1;
    wc->next = hashTable[index];
    hashTable[index] = wc;
    free(key_no_punct);
}


// Функция вывода частот слов с частотой больше 1
void print_frequencies(nodelist *head, FILE *f) {
    nodelist *sorted_list = NULL;
    nodelist *current = head;
    while (current != NULL) {
        if (current->value > 1) {
            nodelist *new_node = (nodelist*) malloc(sizeof(nodelist));
            strcpy(new_node->key, current->key);
            new_node->value = current->value;
            new_node->next = sorted_list;
            sorted_list = new_node;
        }
        current = current->next;
    }

    sort_table(&sorted_list);

    while (sorted_list != NULL) {
        fprintf(f, "%s -> %d\n", sorted_list->key, sorted_list->value);
        nodelist *next = sorted_list->next;
        free(sorted_list);
        sorted_list = next;
    }
}

// Функция для сортировки таблицы
void sort_table(nodelist **head) {
    nodelist *current = *head;
    nodelist *next = NULL;
    nodelist *max = NULL;

    while (current != NULL) {
        max = current;
        next = current->next;
        while (next != NULL) {
            if (next->value > max->value) {
                max = next;
            }
            next = next->next;
        }
        if (max != current) {
            int temp = max->value;
            char temp_key[MAX_WORD_LENGTH];
            strcpy(temp_key, max->key);
            max->value = current->value;
            strcpy(max->key, current->key);
            current->value = temp;
            strcpy(current->key, temp_key);
        }
        current = current->next;
    }
}