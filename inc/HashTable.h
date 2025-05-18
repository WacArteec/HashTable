#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <assert.h>
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOUND 1
#define LOAD_FACTOR 16u
#define NOTFOUND 0u
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
void Insert(HashTable *table, const char *key, size_t i);
size_t Search(HashTable *table, const char *key);
void Delete(HashTable *table, const char *key);

#endif //HASHTABLE_H