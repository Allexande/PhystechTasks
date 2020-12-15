//Version 0.7

//Start of working
bool WriteBeginning (const char* filename);

//Taking derivative body
bool StartOfTakingDerivative (const char* filename, size_t number);

bool WriteSubtree  (const char* filename, DiffNode* node);
void WriteNode     (DiffNode* node, FILE* file);
void WriteInRound  (DiffNode* node, FILE* file);
void WriteInBraces (DiffNode* node, FILE* file);

bool WriteText (const char* filename, const char* text);

//Creating memes
void PicturePic (const char* filename, FILE* file);
void PictureMeme (const char* filename, FILE* file,              \
                size_t Xfirst, size_t Yfirst, DiffNode* first,   \
                size_t Xsecond, size_t Ysecond, DiffNode* second);

//Posting memes
bool WriteDiff (const char* filename, DiffNode* first, DiffNode* second);
bool WriteSimp (const char* filename, DiffNode* first, DiffNode* second);

//End of working
bool WriteEnd (const char* filename);

//Translate TEX to PDF
bool TranslateToPDF (const char* filename);
