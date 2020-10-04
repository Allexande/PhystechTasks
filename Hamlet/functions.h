
//------------------------------------------------
//! Process arguments from main()
//!
//! @param [in] int Number of arguments
//! @param [in] argv Arguments list
//! @param [out] input Pointer on name of file
//!             for reading text from
//! @param [out] output Pointer on name of file
//!             for writing text in
//!
//! @return True if test mod was activated and
//!         false if not
//------------------------------------------------
bool processMainArguments (int argc, char* argv[], char** input, char** output);

//------------------------------------------------
//! Writes text from file in text
//!
//! @param [in] fileName Name of file
//!
//! @return Pointer on text if the file
//!         has been accessed and its content was
//!         written in text, NULL if not
//------------------------------------------------
char* getText (const char *fileName);

//------------------------------------------------
//! Generates pointers on lines in text
//!
//! @param [in] text Pointer on text
//!
//! @return Pointer on pointers on lines in text
//!
//------------------------------------------------
char** getPointers (char* text);

//------------------------------------------------
//! Sort lines alphabetically
//!
//! @param [out] pointers Pointer on pointers on
//!              lines in text
//------------------------------------------------
void sortPointers (char** pointers);

//------------------------------------------------
//! Sort lines alphabetically backwards
//!
//! @param [out] pointers Pointer on pointers on
//!              lines in text
//------------------------------------------------
void sortPointersViseVersa (char** pointers);

//------------------------------------------------
//! Generates poem from random lines of text
//!
//! @param [in] pointers Pointers on pointers on
//!             lines on text
//! @param [in] rhymedPairs How much pairs of
//!             lines of poem to return
//!
//! @return Pointers on pointers of lines of poem
//------------------------------------------------
char** getPointersOfPoem (char** pointers, unsigned int rhymedPairs);

//------------------------------------------------
//! Counts bytes of text file
//!
//! @param [in] fileName Name of file
//!
//! @return Number of bytes in file
//!
//! @note Returns 0 if file has not been accessed
//------------------------------------------------
size_t getNumberOfBytes (const char *fileName);

//------------------------------------------------
//! Counts symbol in text
//!
//! @param [in] text Text in which you count
//! @param [in] symbol Symbol to find
//!
//! @return Number of lines in text
//------------------------------------------------
int getNumberOfSymbol (const char *text, char symbol);

//------------------------------------------------
//! Creates array of pointers there pointers
//! points to strings sorted alphabetically
//!
//! @param [in] fileName Name of file
//!
//! @return Pointer on array of pointers
//------------------------------------------------
char** getSortedArrayOfPointers (const char *fileName);

//------------------------------------------------
//! Determines which line should come first
//! in alphabetical order
//!
//! @param [in] adress1 Pointer on beginning
//!        of the first string
//! @param [in] adress2 Pointer on beginning
//!        of the second string
//! @param [in] direction What add to adresses
//!        during comparison
//!
//! @return True if second string should come
//!         first and false in any other case
//------------------------------------------------
bool comparator (char* adress1, char* adress2, int direction);

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
char getChar (char* adress);

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
bool textOutIntoFIle (const char *fileName, char** pointers);

//------------------------------------------------
//! Reads text from file, sorts it and writes to
//! another file
//!
//! @param [in] Pointer on name of file
//!             for reading text from
//! @param [in] Pointer on name of file
//!             for writing text in
//!
//! @return Number of error or 0 if there are
//!         no errors
//------------------------------------------------
int doSort (const char *input, const char *output);

void writePoem (const char *fileName, unsigned int rhymedPairs); //???

void textOut (char** pointers); //TODO detele this function
