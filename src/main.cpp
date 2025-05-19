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

    printf("\t\n%lu\n", read->count_words);

    HashTable *table = CreateTable(64);

    printf("\t\n%lu\n", read->count_words);
    printf("fdsawer");

    for (size_t i = 0; i < read->count_words; i++)
    {
        printf("fdsawer");
        Insert(table, read->words[i], i);

        int random = rand() % 32;
        char *rand_str = RandString(random);

        printf("fdsawer");

        SearchAsm(table, rand_str);

        free(rand_str);
    }

    printf("\nsize = %lu capacity = %lu\n", table->size, table->capacity);

    DestroyTable(table);
    FreeReader(read);

    printf("\tjhgfds\n");
    return 0;
}