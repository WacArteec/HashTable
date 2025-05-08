#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

#define FOUND 1
#define LOAD_FACTOR 16
#define NOTFOUND 0
#define SIZE_CHANGE 2

struct Cell
{
    char *key;

    size_t value;

    Cell *next;
};

struct HashTable
{
    Cell **buckets;

    size_t size;
    size_t capacity;
};

HashTable *CreateTable(size_t init_capacity);
void DestroyTable(HashTable *table);
void ReHashChains(HashTable *table);
void Insert(HashTable *table, char *key);
size_t Search(HashTable *table, char *key);
void Delete(HashTable *table, char *key);

#endif //HASHTABLE_H