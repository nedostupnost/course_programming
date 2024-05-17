#include "wordsCount.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        fclose(input);
        perror("Error opening output file");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(input, "%s", word) != EOF) {
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]); // Приводим слово к нижнему регистру
        }
        add_word(word);
    }

    nodelist *list = NULL;

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        nodelist *current = hashTable[i];
        while (current != NULL)
        {
            nodelist *next = current->next;
            current->next = list;
            list = current;
            current = next;
        }
    }

    print_frequencies(list, output);

    fclose(input);
    fclose(output);

    return 0;
}
