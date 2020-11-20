//Version 0.4 (Dont work)

#include "game.h"

void StartGame (const char *inputBase, const char *outputBase) {

    printf ("\n\n~ ~ ~ ~ ~ AKINATOR ~ ~ ~ ~ ~\n");
    printf ("inputBase = %s | outputBase = %s\n", inputBase, outputBase);

    Tree* gameTree = GetTreeFromFile (inputBase);

    if (gameTree == NULL) {
        printf ("ERROR: Failed to open file %s\n", inputBase);
        return;
    }

    Menu (gameTree);

    if (gameTree->wasChanged) {
        if (PutTreeToFile (outputBase, gameTree)) {
            printf ("Changed database was saved in %s\n", outputBase);
        } else {
            printf ("ERROR: Failed to open file %s\n", outputBase);
        }
    }

};


void Menu (Tree* base) {

    int input;

    do {

    printf ("\n~ ~ MENU ~ ~\n");

    printf ("You can call one of these commands:\n"
    "[%d] Stop the program                      \n"
    "[%d] Start user version of akinator        \n"
    "[%d] Start developer version of akinator   \n"
    "[%d] Get definition of word                \n"
    "[%d] Compare two words                     \n"
    "[%d] Draw a graph of current database      \n",

    STOP,
    USER_AKINATOR,
    DEV_AKINATOR,
    DEFINITION,
    COMPARISON,
    GRAPH_DUMP
    );

    scanf ("%d", &input);

    switch (input) {

        case STOP: {
            printf ("Akinator stopped.");
        } break;

        case USER_AKINATOR: {
            StartAkinator (base, true);
        } break;

        case DEV_AKINATOR: {
            StartAkinator (base, false);
        } break;

        case DEFINITION: {
            printf ("Oops.... This command does not exist yet.\n");
        } break;

        case COMPARISON: {
            printf ("Oops.... This command does not exist yet.\n");
        } break;

        case GRAPH_DUMP: {
            printf ("Oops.... This command does not exist yet.\n");
        } break;

        default: {
            printf ("Unknown command \"%d\"\n", input);
        } break;

    }

    } while (input != STOP);

}

bool StartAkinator (Tree* thisTree, bool userMode) {

    if (thisTree == NULL || thisTree->root == NULL) {
        return false;
    }

    stack_t* possibleSubs = newStack (DEFAULT_POSSIBLESUB_SIZE);

    AkinatorProcess (thisTree, thisTree->root, possibleSubs, userMode);

    return true;
}

void AkinatorProcess (Tree* thisTree, Node* thisNode, stack_t* possibleSubs, bool userMode) {

    if (thisNode->question) {
        int answer = AskQuestion (thisNode->text);

        switch (answer) {

            case YES: {
                AkinatorProcess (thisTree, thisNode->right, possibleSubs, userMode);
            } break;

            case UNSURE_YES: {
                stackPush (possibleSubs, thisNode->left);
                AkinatorProcess (thisTree, thisNode->right, possibleSubs, userMode);
            } break;

            case UNSURE: {
                //WARNING
                //Behavior in case of UNSURE can be different
                //There it is the same like in UNSURE_YES
                stackPush (possibleSubs, thisNode->left);
                AkinatorProcess (thisTree, thisNode->right, possibleSubs, userMode);
            } break;

            case UNSURE_NO: {
                stackPush (possibleSubs, thisNode->right);
                AkinatorProcess (thisTree, thisNode->left, possibleSubs, userMode);
            } break;

            case NO: {
                AkinatorProcess (thisTree, thisNode->left, possibleSubs, userMode);
            } break;

            default: {
                printf ("Unknown answer \"%d\"\n", answer);
            } break;

        }

    } else {

        if (IsEnvisionedSub (thisNode->text)) {
            printf ("I guessed it!\n");
        } else {
            if (possibleSubs->length < 1) {
                if (userMode) {
                    printf ("It was too hard for me to guess what you were thinking about...\n");
                } else {
                    if (TryToAddNode ()) {
                        thisTree->wasChanged = true;
                        if (AddNewNode (thisNode)) {
                            printf ("New node was added!\n");
                        }
                    }
                }
            } else {
                AkinatorProcess (thisTree, stackPop (possibleSubs), possibleSubs, userMode);
            }
        }
    }
}

int AskQuestion (char* text) {

    int answer;

    printf ("> Is it true, that it %s?\n", text);

    do {

        printf ("You can answer:\n"
        "[%s] Absolutely true   \n"
        "[%s] Probably true     \n"
        "[%s] I have no idea... \n"
        "[%s] Probably false    \n"
        "[%s] Absolutely false  \n",
        YES,
        UNSURE_YES,
        UNSURE,
        UNSURE_NO,
        NO
        );

        scanf ("%d", answer);

        if ((answer >= NO) && (answer <= YES)) {
            return answer;
        } else {
            printf ("Unknown command \"%d\"\n", answer);
        }

    } while (true);
}

bool IsEnvisionedSub (char* text) {

    int answer;

    printf ("> Is it a %s?\n", text);

    do {

        printf ("You can answer:\n"
        "[%s] YES               \n"
        "[%s] NO                \n",
        1,
        0
        );

        scanf ("%d", answer);

        switch (answer) {

            case 0: {
                return false;
            } break;

            case 1: {
                return true;
            } break;

            default: {
                printf ("Unknown command \"%d\"\n", answer);
            } break;
        }

    } while (true);
}

bool TryToAddNode () {

    int answer;

    printf ("> Do you want to add a new node?\n");

    do {

        printf ("You can answer:\n"
        "[%s] YES               \n"
        "[%s] NO                \n",
        1,
        0
        );

        scanf ("%d", answer);

        switch (answer) {

            case 0: {
                return false;
            } break;

            case 1: {
                return true;
            } break;

            default: {
                printf ("Unknown command \"%d\"\n", answer);
            } break;
        }

    } while (true);

}

bool AddNewNode (Node* thisNode) {

    char* newSub;

    printf ("> What you were thinking about?\n");

    scanf ("%s", newSub);

    char* newQuestion;

    printf ("> What special characteristic %s have but %s does not?\n"
    "Continue the phrase: %s ...                                   \n",
    newSub,
    thisNode->text,
    newSub
    );

    scanf ("%s", newQuestion);

   if ((thisNode == NULL) || (newQuestion == NULL) || (newQuestion == NULL)) {
    return false;
   }

   return AddNewSub (thisNode, newSub, newQuestion);

}


