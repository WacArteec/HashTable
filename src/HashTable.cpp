#include "../inc/HashTable.h"

size_t Hash(char *key, size_t capacity)
{
    const size_t shift = 31;
    size_t hash = 0;
    size_t shift_pow = 1;

    while (*key)
    {
        // printf("\t\n%d\n", __LINE__);
        hash += (*key - 'a' + 1) * shift_pow;

        shift_pow *= shift;
        key++;
    }

    return hash % capacity;
}

HashTable *CreateTable(size_t init_capacity)
{
    HashTable *table = (HashTable *)calloc(1, sizeof(HashTable));

    table->capacity = init_capacity;
    table->size = 0;

    table->buckets = (Cell **)calloc(init_capacity, sizeof(Cell *));

    return table;
}

void DestroyTable(HashTable *table)
{
    for (size_t i; i < table->capacity; i++)
    {
        Cell *node = table->buckets[i];

        while (node != NULL)
        {
            Cell *temp = node;
            node = node->next;

            free(temp);
        }
    }

    free(table->buckets);
    table->buckets = NULL;

    free(table);
    table = NULL;
}

void ReHashChains(HashTable *table)
{
    size_t new_capacity = table->capacity * SIZE_CHANGE;

    Cell **new_table = (Cell **)calloc(new_capacity, sizeof(Cell *));

    for (size_t i = 0; i < table->capacity; i++)
    {
        Cell *node = table->buckets[i];

        while (node != NULL)
        {
            Cell *next = node->next;

            size_t new_index = Hash(node->key, new_capacity);

            node->next = new_table[new_index];
            new_table[new_index] = node;

            node = next;
        }
    }

    free(table->buckets);

    table->buckets = new_table;
    table->capacity = new_capacity;
}

void Insert(HashTable *table, char *key)
{
    if (table->size > (size_t)LOAD_FACTOR * table->capacity)
    {
        printf("\t%d %lu %lu\n", __LINE__, table->size, table->capacity);
        ReHashChains(table);
    }

    size_t index = Hash(key, table->capacity);

    Cell *node = table->buckets[index];

    while (node != NULL)
    {
        if (node->key == key)
            return;

        node = node->next;
    }

    Cell *new_node = (Cell *)calloc(1, sizeof(Cell));

    new_node->key = key;
    new_node->next = table->buckets[index];

    table->buckets[index] = new_node;
    table->size++;
}

size_t Search(HashTable *table, char *key)
{
    size_t index = Hash(key, table->capacity);

    Cell *node = table->buckets[index];

    while (node != NULL)
    {
        if (node->key == key)
            return node->value;

        node = node->next;
    }

    return (size_t)NOTFOUND;
}

void Delete(HashTable *table, char *key)
{
    size_t index = Hash(key, table->capacity);

    Cell *node = table->buckets[index];
    Cell **node_ptr = &table->buckets[index];

    while (node != NULL)
    {
        if (node->key == key)
        {
            *node_ptr = node->next;

            table->size--;

            free(node);
            return;
        }

        node_ptr = &node->next;
        node = node->next;
    }
}