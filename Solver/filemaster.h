//Version 1.0

struct Lines {

    //The text of lines
    char** line;

    //Number of lines
    size_t numberOfLines;

};

//Work with info from file
size_t GetNumberOfBytesOfFile (const char* fileName);
char*  ReadTextFromFile       (const char* fileName);

//Write to file
bool WriteTextInFile (const char* fileName, char* text);

//Work with strings
Lines* GetLinesFromText  (char* text);
size_t GetNumberOfSymbol (const char* text, char symbol);
