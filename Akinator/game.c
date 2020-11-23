//Version 1.1

#include "game.h"

void StartGame (const char* inputBase, const char* outputBase) {

    printf ("\n\n~ ~ ~ ~ ~ AKINATOR ~ ~ ~ ~ ~\n");
    printf ("inputBase = %s | outputBase = %s\n", inputBase, outputBase);

    Tree* gameTree = GetTreeFromFile (inputBase);

    if (gameTree == NULL) {
        printf ("ERROR: Failed to read from file %s\n", inputBase);
        return;
    }

    Menu (gameTree);

    if (gameTree->wasChanged) {
        if (PutTreeToFile (outputBase, gameTree)) {
            printf ("Changed database was saved in %s\n", outputBase);
        } else {
            printf ("ERROR: Failed to write in file %s\n", outputBase);
        }
    }

    DestroyTree (gameTree);
}

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
                printf ("Akinator stopped.\n");
            } break;

            case USER_AKINATOR: {
                StartAkinator (base, true);
            } break;

            case DEV_AKINATOR: {
                StartAkinator (base, false);
            } break;

            case DEFINITION: {
                Define (base);
            } break;

            case COMPARISON: {
                Compare (base);
            } break;

            case GRAPH_DUMP: {
                GraphTree (base);
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
        ProcessQuestion (thisTree, thisNode, possibleSubs, userMode);
        return;
    }

    if (IsEnvisionedSub (thisNode->text)) {
        printf ("I guessed it!\n");
        return;
    }

    if (possibleSubs->length < 1) {
        if (userMode) {
            printf ("It was too hard for me to guess what you were thinking about...\n");
            return;
        }

        if (TryToAddNode ()) {
            thisTree->wasChanged = true;
            if (AddNewNode (thisTree, thisNode)) {
                printf ("New node was added!\n");
            }
        }

        return;
    }

    AkinatorProcess (thisTree, stackPop (possibleSubs), possibleSubs, userMode);
}

void ProcessQuestion (Tree* thisTree, Node* thisNode, stack_t* possibleSubs, bool userMode) {

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
}

int AskQuestion (char* text) {

    int answer;

    printf ("> Is it true, that it %s?\n", text);

    do {

        printf ("You can answer:\n"
        "[%d] Absolutely true   \n"
        "[%d] Probably true     \n"
        "[%d] I have no idea... \n"
        "[%d] Probably false    \n"
        "[%d] Absolutely false  \n",
        YES,
        UNSURE_YES,
        UNSURE,
        UNSURE_NO,
        NO
        );

        scanf ("%d", &answer);

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
        "[%d] YES               \n"
        "[%d] NO                \n",
        1,
        0
        );

        scanf ("%d", &answer);

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
        "[%d] YES               \n"
        "[%d] NO                \n",
        1,
        0
        );

        scanf ("%d", &answer);

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

bool AddNewNode (Tree* thisTree, Node* thisNode) {

      char* newSub = (char*) calloc (sizeof(char), MAXIMUM_TEXT_SIZE);
    assert (newSub);

    printf ("> What you were thinking about?\n");

    scanf ("\n%[^\n]s", newSub);

      char* newQuestion = (char*) calloc (sizeof(char), MAXIMUM_TEXT_SIZE);
    assert (newQuestion);

    printf ("> What special characteristic %s have but %s does not?\n"
    "Continue the phrase: %s ...                                   \n",
    newSub,
    thisNode->text,
    newSub
    );

    scanf ("\n%[^\n]s", newQuestion);

   if ((thisNode == NULL) || (newQuestion == NULL) || (newQuestion == NULL)) {
        return false;
   }

   return AddNewSub (thisTree, thisNode, newSub, newQuestion);
}

bool Compare (Tree* thisTree) {

      char* first = (char*) calloc (sizeof(char), MAXIMUM_TEXT_SIZE);
    assert (first);

      char* second = (char*) calloc (sizeof(char), MAXIMUM_TEXT_SIZE);
    assert (second);

    printf ("> What is the first subject you want to compare?\n");

    scanf ("\n%[^\n]s", first);

    printf ("> What is the second subject you want to compare?\n");

    scanf ("\n%[^\n]s", second);

    if ((first != NULL) && (second != NULL) && (thisTree != NULL)) {

        if (!TryToCompare (thisTree, first, second)) {
            printf("Oops... you entered words which don't exist in the database.\n");
            return false;
        }

        return true;
    }

    return false;
}

bool TryToCompare (Tree* thisTree, char* first, char* second) {

    Node* firstNode  = NULL;
    Node* secondNode = NULL;

    size_t pointer = 0;
    while (thisTree->subjects[pointer] != NULL) {

        if (strcmp (thisTree->subjects[pointer]->text, first) == 0) {
            firstNode = thisTree->subjects[pointer];
        }

        if (strcmp (thisTree->subjects[pointer]->text, second) == 0) {
            secondNode = thisTree->subjects[pointer];
        }

        pointer++;
    }

    if ((firstNode != NULL) && (secondNode != NULL)) {
        WriteComparation (thisTree, firstNode, secondNode);
        return true;
    }

    return false;
}

void WriteComparation (Tree* thisTree, Node* first, Node* second) {

    Node* firstSame = FindFirstSame (first, second);

     Node* link = (Node*) calloc (sizeof(Node), 1);
    assert(link);

    link = first;

    if (link != firstSame) {
        printf ("We know something about %s. For example,", first->text);
    }

    while (link->parent != firstSame) {

        if (link->parent->right == link) {
                printf (" it ");
            } else {
                printf (" it is false that it ");
            }

        printf ("%s,", link->parent->text);

        link = link->parent;
    }

    link = second;
    Node* previousSecond = second;

    if (link->parent != firstSame) {
        printf ("We know something about %s. For example,", second->text);
    }

    while (link->parent != firstSame) {

        if (link->parent->right == link) {
                printf (" it ");
            } else {
                printf (" it is false that it ");
            }

        printf ("%s,", link->parent->text);

        previousSecond = link;
        link = link->parent;
    }

    printf ("There is a difference between %s and %s. ", first->text, second->text);
    if (previousSecond == firstSame->right) {
        printf ("%s %s, but it is false for %s. ", first->text, firstSame->text, second->text);
    } else {
        printf ("%s %s, but it is false for %s. ", second->text, firstSame->text, first->text);
    }

    printf ("As for similarities,");

    while (firstSame->parent != NULL) {

        if (firstSame->parent->right == firstSame) {
            printf (" they ");
        } else {
            printf (" it is false that they ");
        }

        printf ("%s,", firstSame->text);

        firstSame = firstSame->parent;

    }

    printf (" and that is all.\n");
}

bool Define (Tree* thisTree) {

      char* subject = (char*) calloc (sizeof(char), MAXIMUM_TEXT_SIZE);
    assert (subject);

    printf ("> What is the subject you want to get definition of?\n");

    scanf ("\n%[^\n]s", subject);

    if ((subject != NULL) && (thisTree != NULL)) {

        if (!TryToDefine (thisTree, subject)) {
            printf("Oops... you entered word which don't exist in the database.\n");
            return false;
        }

        return true;
    }

    return false;
}

bool TryToDefine (Tree* thisTree, char* subject) {

    Node* subjectNode = NULL;

    size_t pointer = 0;
    while (thisTree->subjects[pointer] != NULL) {

        if (strcmp (thisTree->subjects[pointer]->text, subject) == 0) {
            subjectNode = thisTree->subjects[pointer];
        }

        pointer++;
    }

    if (subjectNode != NULL) {

        printf ("\nThe defenition of %s:", subject);
        WriteDefinition (thisTree, subjectNode);
        printf (" and that is all.\n");

        return true;
    }

    return false;

}

void WriteDefinition (Tree* thisTree, Node* subject) {

    if (subject->parent->right == subject) {
        printf (" it ");
    } else {
        printf (" it is false that it ");
    }

    printf ("%s,", subject->parent->text);

    if (subject->parent != thisTree->root) {
        WriteDefinition (thisTree, subject->parent);
    }
}
