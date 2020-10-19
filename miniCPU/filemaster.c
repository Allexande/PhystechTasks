size_t getNumberOfBytesOfFile (const char *fileName) {

    assert (fileName);

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return 0;

    } else {
        fseek(file, 0, SEEK_END);
        size_t pos = ftell(file);
        fseek(file, 0, SEEK_SET);
        fclose (file);
        return pos;
    }
};

char* readTextFromFile (const char *fileName) {

    assert (fileName);

    size_t length = getNumberOfBytesOfFile (fileName);

    if (length < 1) {
        return NULL;
    }

    char* text = (char *) calloc (length + 2, sizeof(char));

    FILE *file = fopen (fileName, "r");

    if (file == NULL) {
        return NULL;

    } else {
        int lengthWasRead = fread ((text), sizeof(char), length, file);
        fclose (file);
        *(text+lengthWasRead) = '\0';
        return text;
    }
};
