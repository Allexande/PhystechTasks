
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
//! @return True if more that 1 argument was
//!         processed and false if none
//------------------------------------------------
bool processMainArguments(int argc, char* argv[], char** input, char** output);

//------------------------------------------------
//! Writes text from file in text
//!
//! @param [in] fileName Name of file
//! @param [out] text Variable for text
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
//! @param [in] fileName Name of file
//!
//! @return Pointer on array of pointers
//!
//! @note In case of error returns NULL
//------------------------------------------------
char** getSortedArrayOfPointers(const char *fileName);

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
bool comparator(char* adress1, char* adress2);

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
char getChar(char* adress);

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
int doSort(const char *input, const char *output);

void textOut(char** pointers); //TODO detele this function
