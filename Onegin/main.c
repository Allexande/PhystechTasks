#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "text.txt"


bool getText(const char *fileName, char* text);

int getNumberOfBytes(const char *fileName);

int getNumberOfLines(const char *text, int length);

bool fillArrayOfPointers(char** pointers);

int main()
{

    char* txt;
    txt = (char *) calloc(getNumberOfBytes(FILE_NAME), sizeof(char));
    if(getText(FILE_NAME, txt)){
            printf("%d\n", getNumberOfLines(txt, getNumberOfBytes(FILE_NAME)));
            for(int i=0; i<getNumberOfBytes(FILE_NAME);i++){
                printf("%d %ld %c\n", i, &txt[i], txt[i]);
            }
    } else {
        printf("%s\n", "ERROR");
    }

    char** pointers;
    fillArrayOfPointers(pointers);
    for(int i = 0; i < getNumberOfLines(txt, getNumberOfBytes(FILE_NAME)); i++){
        printf("%d %s %ld\n", i, "pointers[i] = ", pointers[i]);
    }

    return 1;
}

bool fillArrayOfPointers(char** pointers){
    int length = getNumberOfBytes(FILE_NAME);
    if(length < 1) return false;
    char* text = (char *) calloc(length, sizeof(char));

    if(getText(FILE_NAME, text)){
        int numberOfLines = getNumberOfLines(text, length);

        pointers = (char **) calloc(numberOfLines, sizeof(char));
        for(int i = 0; i < length; i++){
            if(text[i] == '\n'){
                pointers[i] = &text[i];
            }
        }

        return true;
    } else {
        return false;
    }
};

int getNumberOfLines(const char *text, int length){
    int lines = 1;
    for(int i = 0; i < length; i++){
        if(text[i] == '\n') lines++;
    }
    return lines;
};

int getNumberOfBytes(const char *fileName){
    FILE *file;

    if ((file = fopen(fileName, "r")) == NULL) {
        return -1;
    } else {
        int number = 0;
        char sym;
        while((sym = fgetc(file)) != EOF){ // -!!!!!
            number++;
        }
        fclose(file);
        return number;
    }
};

bool getText(const char *fileName, char* text){
    FILE *file;

    if ((file = fopen(fileName, "r")) == NULL) {
        return false;
    } else {
        int numberOfSymbol = -1;
        while(*(text+(numberOfSymbol++)) != EOF){
            fscanf(file, "%c", text+(numberOfSymbol));
        }
        fclose(file);
        return true;
    }
};


