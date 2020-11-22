//Version 0.8

struct Lines {
    //The text of lines
    char** line;
    //Number of lines
    size_t numberOfLines;
};

enum DatabaseError {
    IS_OK         = 0, //Database is OK
    EMPTY         = 1, //Database is empty
    TOO_DEEP      = 2, //Database creates tree deeper than MAXIMUM_TREE_DEEP
    OPEN_BLOCK    = 3, //Database have wrong structure: there is block without closing
    WRONG_BLOCKS  = 4, //Database have wrong structure: there is brackets at wrong place
    WRONG_DIVIDER = 5, //Database contains bracket divider with rubbish after it
    WRONG_BEGIN   = 6, //Database contains line which do not begin with bracket
    WRONG_END     = 7, //Database contains line which do not end with bracket
    WRONG_LINE    = 8  //Database contains line which have rubbish after bracket
};

size_t GetNumberOfBytesOfFile (const char *fileName);

char* ReadTextFromFile (const char *fileName);

bool WriteTextInFile (const char *fileName, char* text);

Lines* GetLinesFromText (char* text);

size_t GetNumberOfSymbol (const char *text, char symbol);

bool FilesContainSameText (const char *first, const char *second);

int CheckIfTextIsDatabase (char* text);

DatabaseError CheckLine (char* line);
