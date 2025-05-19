#include "../inc/HashTable.h"

extern size_t SearchAsm(const HashTable* table, const char* key);

size_t Hash_CRC32(const char* key, size_t capacity)
{
    size_t hash = 0xffffffff;

    while (*key)
    {
        key++;
        hash = _mm_crc32_u8(hash, (unsigned char)(*key));
    }

    return hash % capacity;
}

size_t Hash(const char *key, size_t capacity)
{    
    const size_t shift = 31;
    size_t hash = 0;
    size_t shift_pow = 1;

    while (*key)
    {
        // printf("\t\n%d\n", __LINE__);
        hash = (hash + (*key - 'a' + 1) * shift_pow) % capacity;
        shift_pow = (shift_pow * shift) % capacity;

        key++;
    }

    return hash % capacity;
    
}

HashTable *CreateTable(size_t init_capacity)
{
    HashTable *table = (HashTable *)calloc(1, sizeof(HashTable));
    assert(table);

    table->capacity = init_capacity;
    table->size = 0;

    table->buckets = (Cell **)calloc(init_capacity, sizeof(Cell *));
    assert(table->buckets);

    return table;
}

void DestroyTable(HashTable *table)
{
    assert(table);

    for (size_t i = 0; i < table->capacity; i++)
    {
        Cell *node = table->buckets[i];

        while (node != NULL)
        {
            Cell *temp = node;
            node = node->next;

            free(temp->key);
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
    assert(table);

    size_t new_capacity = table->capacity * SIZE_CHANGE;

    Cell **new_table = (Cell **) calloc(new_capacity, sizeof(Cell *));
    assert(new_table);

    for (size_t i = 0; i < table->capacity; i++)
    {
        Cell *node = table->buckets[i];

        while (node != NULL)
        {
            Cell *next = node->next;

            size_t new_index = Hash_CRC32(node->key, new_capacity);

            node->next = new_table[new_index];
            new_table[new_index] = node;

            node = next;
        }
    }

    free(table->buckets);

    table->buckets = new_table;
    table->capacity = new_capacity;
}

int AsmStrcmp(const char *a, const char *b)
{
    int result;

    __asm
    (
        "1:\n"
        "movb (%0), %%al\n"     // Загружаем байт из a
        "cmpb (%1), %%al\n"     // Сравниваем с байтом из b
        "jne 2f\n"              // Если не равны -> выход
        "inc %0\n"              // Переходим к следующему символу
        "inc %1\n"
        "test %%al, %%al\n"     // Проверяем на конец строки
        "jnz 1b\n"              // Если не конец -> повторяем
        "2:\n"
        "sete %%cl\n"           // Устанавливаем результат (1 если равны)
        "movzbl %%cl, %2\n"
        : "+r" (a), "+r" (b), "=r" (result)
        : 
        : "rax", "rcx", "cc"
    );
    
    return (1-result);
}

int NodeIterating(Cell *node, const char *key)
{
    while (node != NULL)
    {
        if (AsmStrcmp(node->key, key) == 0)
        {
            node->value++;
            return FOUND;
        }

        node = node->next;
    }

    return NOTFOUND;
}

void Insert(HashTable *table, const char *key, size_t i)
{
    assert(table);

    if (table->size > LOAD_FACTOR * table->capacity)
    {
        printf("\t%d %lu %lu\n", __LINE__, table->size, table->capacity);
        ReHashChains(table);
    }

    size_t index = Hash_CRC32(key, table->capacity);

    Cell *node = table->buckets[index];

    if(NodeIterating(node, key) == FOUND)
        return;

    Cell *new_node = (Cell *)calloc(1, sizeof(Cell));
    assert(new_node);

    new_node->key = strdup(key);
    if (!new_node->key)
    {
        free(new_node);
        return;
    }

    new_node->value = 1;

    new_node->next = table->buckets[index];

    table->buckets[index] = new_node;
    table->size++;
}

size_t Search(HashTable *table, const char *key)
{
    assert(table);

    size_t index = Hash_CRC32(key, table->capacity);

    Cell *node = table->buckets[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;

        node = node->next;
    }

    return NOTFOUND;
}

void Delete(HashTable *table, const char *key)
{
    assert(table);

    size_t index = Hash_CRC32(key, table->capacity);

    Cell *node = table->buckets[index];
    Cell **node_ptr = &table->buckets[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            *node_ptr = node->next;

            table->size--;

            free(node->key);
            free(node);

            return;
        }

        node_ptr = &node->next;
        node = node->next;
    }
}