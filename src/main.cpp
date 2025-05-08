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

void Insertion(HashTable *table, Reader *read)
{
    for (size_t i = 0; i < read->count_words / 1.5; i++)
        Insert(table, read->words[i]);
}

int main()
{
    Reader *read = Input("WarAndPeace.txt");
 
    //for (size_t i = 0; i < read->count_words; i++)
        //printf("%s", read->words[i]);
    
    printf("\t\n%lu\n", read->count_words);

    HashTable *table = CreateTable(64);

    //Insertion(table, read);

    printf("\t\n%lu\n", read->count_words);

    for (size_t i = 0; i < read->count_words/2; i++)
    {
        Insert(table, read->words[i]);
        //printf("\t\n%d\n", __LINE__);
        int random = rand() % 32;

        char *rand_str = RandString(random);

        //printf("%llu %d %s", i, random, rand_str);
        Search(table, rand_str);

        free(rand_str);
    }

    DestroyTable(table);
    FreeReader(read);

    printf("\tjhgfds\n");
    return 0;
}