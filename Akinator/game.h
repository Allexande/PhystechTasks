//Version 1.0

#include "akinator.c"

enum Actions {
    STOP          = 0,
    USER_AKINATOR = 1,
    DEV_AKINATOR  = 2,
    DEFINITION    = 3,
    COMPARISON    = 4,
    GRAPH_DUMP    = 5
};

enum Answer {
    NO         = -2,
    UNSURE_NO  = -1,
    UNSURE     = 0,
    UNSURE_YES = 1,
    YES        = 2
};

//Start game
void StartGame (const char* inputBase, const char* outputBase);

//Menu with options
void Menu (Tree* gameTree);

//Akinator process
bool StartAkinator   (Tree* thisTree, bool userMode);
void AkinatorProcess (Tree* thisTree, Node* thisNode, stack_t* possibleSubs, bool userMode);
int AskQuestion      (char* text);

//Adding new nodes
bool IsEnvisionedSub (char* text);
bool TryToAddNode    ();
bool AddNewNode      (Tree* thisTree, Node* thisNode);

//Other options
bool Compare          (Tree* thisTree);
bool TryToCompare     (Tree* thisTree, char* first, char* second);
void WriteComparation (Tree* thisTree, Node* first, Node* second);

bool Define           (Tree* thisTree);
bool TryToDefine      (Tree* thisTree, char* subject);
void WriteDefinition  (Tree* thisTree, Node* subject);

