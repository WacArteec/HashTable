#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include "../inc/Reader.h"

#include <stdio.h>
#include <stdlib.h>

void FileInput(struct Reader *read);
void ReplaceSymbol(struct Reader *read);
int WordCounter(struct Reader *read);
unsigned int MyFstat(struct Reader *read);
char **CreateWordsArray(struct Reader *read);

Reader *Input(const char *filename)
{
    //$$$ printf("%d\n", __LINE__);
    Reader *read = (Reader *)calloc(1, sizeof(Reader));

    //$$$ printf("%d\n", __LINE__);

    read->input_file = filename;

    //$$$ printf("%d\n", __LINE__);

    FileInput(read);
    //$$$ printf("%d\n", __LINE__);

    ReplaceSymbol(read);
    //$$$ printf("%d\n", __LINE__);

    read->count_words = WordCounter(read);
    //$$$ printf("%d\n", __LINE__);

    read->words = CreateWordsArray(read);

    return read;
}

void FileInput(struct Reader *read)
{
    read->file = fopen(read->input_file, "rb");
    $$$ assert(read->file);

    read->count_elements = MyFstat(read);

    read->text = (char *)calloc(read->count_elements + 1, sizeof(char));
    $$$ assert(read->text);

    size_t fread_check = fread(read->text, sizeof(char), read->count_elements, read->file);
    $$$ assert(read->count_elements == fread_check);

    read->text[read->count_elements] = '\0';

    int errclose = !fclose(read->file);
    $$$ assert(errclose); //! NDEBUG! !change to if!
}

int WordCounter(struct Reader *read)
{
    int count_of_words = 1;
    bool in_word = false;

    for (size_t i = 0; i < read->count_elements; i++)
    {
        if (read->text[i] != '\0' && !in_word)
        {
            in_word = true;
            count_of_words++;
        }

        else if (read->text[i] == '\0')
            in_word = 0;
    }

    return count_of_words;
}

void ReplaceSymbol(struct Reader *read)
{
    for (size_t i = 0; i < read->count_elements; i++)
    {
        if (read->text[i] == '\r' || read->text[i] == ' ' || read->text[i] == '\t' || read->text[i] == '\n')
        {
            read->text[i] = '\0';
            // read->text[i+1] = '\0';
        }
    }
}

unsigned int MyFstat(struct Reader *read)
{
    int fseek_proof = fseek(read->file, 0, SEEK_END);
    $$$ assert(fseek_proof + 1);

    unsigned int count_symb_in_file = ftell(read->file);

    $$$ if (read->count_elements == (size_t)(-1L))
        printf("!File Size is 0!");

    rewind(read->file);

    return count_symb_in_file;
}

char **CreateWordsArray(struct Reader *read)
{
    char **words = (char **)calloc(read->count_words + 1, sizeof(char *));
    assert(words != NULL);

    int word_index = 0;
    int in_word = 0;

    for (size_t i = 0; i < read->count_elements; i++)
    {
        if (read->text[i] != '\0' && !in_word)
        {
            words[word_index++] = &read->text[i];
            in_word = 1;
        }

        else if (read->text[i] == '\0')
            in_word = 0;
    }

    words[word_index] = NULL;

    return words;
}

void FreeReader(Reader *read)
{
    if (read)
    {
        free(read->words);
        free(read->text);
        free(read);
    }
}