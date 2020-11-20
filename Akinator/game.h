//Version 0.4 (Dont work)

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
void StartGame (const char *inputBase, const char *outputBase);

//Menu with options
void Menu (Tree* gameTree);

//Akinator process
bool StartAkinator   (Tree* thisTree, bool userMode);
void AkinatorProcess (Tree* thisTree, Node* thisNode, stack_t* possibleSubs, bool userMode);

int AskQuestion (char* text);

bool IsEnvisionedSub (char* text);

bool TryToAddNode ();

bool AddNewNode (Node* thisNode);
