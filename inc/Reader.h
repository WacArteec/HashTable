#ifndef READER_H
#define READER_H

#define $$$

struct Reader
{
    char *text = NULL;
    char **words = NULL;

    size_t count_words = 0;
    size_t count_elements = 0;

    FILE *file = NULL;
    const char *input_file = NULL;
};

Reader *Input(const char *filename);
void FreeReader(Reader *read);

#endif // READER_H