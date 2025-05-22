#include <stdio.h>
#include <stdlib.h>
#include "../inc/Reader.h"
#include "../inc/HashTable.h"

char *RandString(int len)
{
    char *s = (char *)calloc(len + 1, sizeof(char));

    for (size_t i = 0; i < len; i++)
        s[i] = 'a' + rand() % 26;

    s[len] = '\0';

    return s;
}

int main()
{
    Reader *read = Input("WarAndPeace.txt");

    printf("\t\ncount of words: %lu\n", read->count_words);

    HashTable *table = CreateTable(64);

    for (size_t i = 0; i < read->count_words; i++)
    {
        Insert(table, read->words[i], i);

        if (table->size > LOAD_FACTOR * table->capacity)
        {
            printf("\n\t need to rehash: size = %lu, capacity = %lu\n", table->size, table->capacity);
            ReHashChains(table);
        }

        int random = rand() % 24;
        char *rand_str = RandString(random);

        Search(table, rand_str);

        free(rand_str);
    }

    printf("\n unique words (size) = %lu capacity = %lu\n", table->size, table->capacity);

    DestroyTable(table);
    FreeReader(read);

    printf("\tend\n");
    return 0;
}