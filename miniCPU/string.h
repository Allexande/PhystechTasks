//version 0.1.3
struct FunctionalString {
    char* str;
    size_t length;
};

FunctionalString* createFunctionalString (size_t capacity);

FunctionalString* convertToFunctionalString (char* str);

bool compareFunctionalStrings (FunctionalString* first, FunctionalString* second);

FunctionalString* cutFunctionalString (FunctionalString* str, size_t left, size_t right);

FunctionalString* mergeFunctionalStrings (FunctionalString* first, FunctionalString* second);
