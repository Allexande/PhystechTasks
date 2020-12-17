//Version 0.7

#include "random.c"

enum NumberOfMemes {
    DIFF_MEMES_NUMBER = 5,
    SIMP_MEMES_NUMBER = 5
};

//Start of working
bool WriteBeginning (const char* filename);

//Taking derivative body
bool StartOfTakingDerivative (const char* filename, size_t number);
bool EndOfTakingDerivative   (const char* filename, DiffNode* node);

bool WriteSubtree  (const char* filename, DiffNode* node);
void WriteNode     (DiffNode* node, FILE* file);
void WriteInRound  (DiffNode* node, FILE* file);
void WriteInBraces (DiffNode* node, FILE* file);

bool WriteText (const char* filename, const char* text);

//Creating memes
void PicturePic (const char* filename, FILE* file);
void PictureMeme (const char* filename, FILE* file,              \
                int Xfirst, int Yfirst, DiffNode* first,   \
                int Xsecond, int Ysecond, DiffNode* second);

//Posting memes
bool WriteDiff (const char* filename, DiffNode* first, DiffNode* second);
bool WriteSimp (const char* filename, DiffNode* first, DiffNode* second);

bool PostMeme (FILE* file, bool isDiffMeme, DiffNode* first, DiffNode* second);

//End of working
bool WriteEnd (const char* filename);

//Translate TEX to PDF
/*
void TranslateToPDF (const char* filename);
*/

//Work with strings
char* UniteStrings ( char* first,  char* second);
char* IntToString  (int numToConvert);
