//Version 0.5

//Start of working
bool WriteBeginning (const char* filename);

//Taking derivative body
bool StartOfTakingDerivative (const char* filename, size_t number);

bool WriteSubtree  (const char* filename, DiffNode* node);
void WriteNode     (DiffNode* node, FILE* file);
void WriteInRound  (DiffNode* node, FILE* file);
void WriteInBraces (DiffNode* node, FILE* file);

//End of working
bool WriteEnd (const char* filename);

//Translate TEX to PDF
bool TranslateToPDF (const char* filename);
