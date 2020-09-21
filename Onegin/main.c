#include <stdio.h>
#include <stdlib.h>

#define READING_FILE_NAME "text.txt"
#define WRITING_FILE_NAME "sorted.txt"

//------------------------------------------------
//! Writes text from file in text
//!
//! @param [in] fileName Name of file
//! @param [in] text Variable for text
//!
//! @return True if the file has been accessed
//!         and its content was written in text,
//!         false if not
//------------------------------------------------
bool getText(const char *fileName, char* text);

//------------------------------------------------
//! Counts bytes of text file
//!
//! @param [in] fileName Name of file
//!
//! @return Number of bytes in file
//!
//! @note Returns -1 if file has not been accessed
//------------------------------------------------
int getNumberOfBytes(const char *fileName);

//------------------------------------------------
//! Counts lines in text
//!
//! @param [in] text Text in which you count
//! @param [in] length Number of bytes in text
//!
//! @return Number of lines in text
//------------------------------------------------
int getNumberOfLines(const char *text, int length);

//------------------------------------------------
//! Creates array of pointers there pointers
//! points to strings sorted alphabetically
//!
//! @return Pointer on array of pointers
//!
//! @note In case of error returns NULL
//------------------------------------------------
char** getSortedArrayOfPointers();

//------------------------------------------------
//! Determines which line should come first
//! in alphabetical order
//!
//! @param [in] adress1 Pointer on beginning
//!        of the first string
//! @param [in] adress2 Pointer on beginning
//!        of the second string
//!
//! @return True if second string should come
//!         first and false in any other case
//------------------------------------------------
bool comparator(char** adress1, char** adress2);

//------------------------------------------------
//! Gets char from the pointer on char and
//! converts to lowercase
//!
//! @param [in] adress Pointer on beginning
//!        of the string
//!
//! @return Char on which adress pointed to
//!
//! @note Returns NULL if char is not an
//! english letter or newline character
//------------------------------------------------
char getChar(char** adress);

//------------------------------------------------
//! Writes text in file
//!
//! @param [in] fileName Name of file
//! @param [in] pointers Pointer on array
//!             of pointers
//!
//! @return True if the file has been accessed
//!         and content was written in it,
//!         false if not
//------------------------------------------------
bool textOutIntoFIle(const char *fileName, char** pointers);

void textOut(char** pointers); //TODO detele this function

int main()
{
    char** pointers = getSortedArrayOfPointers();
    if(pointers == NULL){
        Printf("ERROR File for reading has not been accessed");
        exit(-1);
    }
    if(!textOutIntoFIle(WRITING_FILE_NAME, pointers)){
        Printf("ERROR File for writing has not been accessed");
        exit(-1);
    }
    textOut(pointers);
    return 1;
};

bool textOutIntoFIle(const char *fileName, char** pointers){
    FILE *file;

    if ((file = fopen(fileName, "w")) == NULL) {
        return false;
    } else {

        int point = 0;
        int symbol = 0;
        char sum;
        while(true){
            sum = *(pointers[point]+symbol);
            if((int)sum == (int)'\n'){
                point++;
                symbol = 0;
                fputc('\n', file);
            } else {
                if(sum == NULL){
                    break;
                }
                fputc(sum, file);
                symbol++;
            }

        }

        fclose(file);
        return true;
    }
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
    int sym = 0;

    char char1 = getChar(adress1);
    char char2 = getChar(adress2);

    while(((int)char1 != (int)'\n') && ((int)char2 != (int)'\n')){
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


