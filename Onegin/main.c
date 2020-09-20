#include <stdio.h>
#include <stdlib.h>

#define READING_FILE_NAME "text.txt"
#define WRITING_FILE_NAME "sorted.txt"

bool getText(const char *fileName, char* text);

int getNumberOfBytes(const char *fileName);

int getNumberOfLines(const char *text, int length);

char** getSortedArrayOfPointers();

bool comparator(char** adress1, char** adress2);

char getChar(char** adress);

void textOut(char** pointers); //TODO detele this function

int main()
{
    char** pointers = getSortedArrayOfPointers();
    textOut(pointers);

    return 1;
};

void textOut(char** pointers){
    int point = 0;
    int symbol = 0;
    char sum;
    while(true){
        sum = *(pointers[point]+symbol);
        if((int)sum == (int)'\n'){
            point++;
            symbol = 0;
            printf("\n");
        } else {
            if(sum == NULL){
                break;
            }
            printf("%c", sum);
            symbol++;
        }

    }
};

char** getSortedArrayOfPointers(){
    int length = getNumberOfBytes(READING_FILE_NAME);
    if(length < 1) return NULL;
    char* text = (char *) calloc(length, sizeof(char));



    if(getText(READING_FILE_NAME, text)){
        int numberOfLines = getNumberOfLines(text, length);
        char** pointers = (char **) calloc(numberOfLines, sizeof(char*));;
        int pointer = 1;
        pointers[0] = &text[0];
        for(int i = 1; i < length-1; i++){
            if(text[i] == '\n'){
                pointers[pointer] = (&text[i]+1);
                pointer++;
            }
        }

        for(int i = 1; i < numberOfLines; i++){

            for(int j = 0; j < numberOfLines - i - 1; j++) {
                if(comparator(&pointers[j], &pointers[j+1])){
                    char* buf = pointers[j];
                    pointers[j] = pointers[j+1];
                    pointers[j+1] = buf;
                }
            }

        }

        pointers[numberOfLines] = NULL;

        return pointers;
    } else {
        return NULL;
    }
};

bool comparator(char** adress1, char** adress2){
    /*printf("%c %c \n", **adress1, **adress2);
    printf("%c %c \n", **(adress1+1), **(adress2));*/
    int sym = 0;

    char char1 = getChar(adress1);
    char char2 = getChar(adress2);

    while(((int)char1 != (int)'\n') && ((int)char2 != (int)'\n')){
        //printf("HEY %c %c\n", char1, char2);
        //printf("adresses are %ld %ld\n", adress1, adress2);
        //printf("(int)char1=%d (int)char2=%d\n", (int)char1, (int)char2);
        if((char1 != NULL) && (char2 != NULL)){
            if((int)char1 != (int)char2){
                return ((int)char1 > (int)char2);
            }
        }
        if((char1 != NULL) && ((int)char1 == (int)char2)){
            adress1++;
            adress2++;
        }
        if(char1 == NULL) adress1++;
        if(char2 == NULL) adress2++;
        char1 = getChar(adress1);
        char2 = getChar(adress2);
    }
    return false;
};

char getChar(char** adress){
    char charFromAdress = **(adress);
    if(((int)charFromAdress >= (int)'A') && ((int)charFromAdress <= (int)'Z')){
        return (charFromAdress+32);
    } else {
        if(((int)charFromAdress >= (int)'a') && ((int)charFromAdress <= (int)'z') || ((int)charFromAdress == (int)'\n')){
            return charFromAdress;
        } else {
            return NULL;
        }
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
        while(fgetc(file) != EOF){
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


