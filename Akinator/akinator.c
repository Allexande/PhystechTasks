//Version 0.7

#include "akinator.h"

Tree* CreateEmptyTree () {

    Tree* newTree = (Tree*) calloc (sizeof(Tree), 1);
    assert (newTree);

    newTree->root       = NULL;
    newTree->subjects   = NULL;
    newTree->wasChanged = false;

    return newTree;
}

Node* CreateEmptyNode () {

    Node* newNode = (Node*) calloc (sizeof(Node), 1);
    assert (newNode);

    newNode->question = false;
    newNode->parent   = NULL;
    newNode->text     = NULL;
    newNode->right    = NULL;
    newNode->left     = NULL;

    return newNode;
}

Tree* GetTreeFromFile (const char *fileName) {

    if (fileName == NULL) {
        return NULL;
    }

    char* textFromFile = ReadTextFromFile (fileName);
    if (textFromFile == NULL) {
        return NULL;
    }

    Tree* newTree = CreateEmptyTree ();
    assert (newTree);

    Lines* linesOfText = GetLinesFromText (textFromFile);
    assert (linesOfText);

    //Link to processing node
    Node* link;
    //Making of first node (root of tree)
    link = CreateEmptyNode ();
    link->text = CutBothSides (linesOfText->line[0]);
    newTree->root = link;

    //Adding other nodes
    for (size_t readingLine = 1; readingLine < linesOfText->numberOfLines; readingLine++) {

        if (strcmp(linesOfText->line[readingLine], "{") == 0) {

            link->question = true;

            Node* newNode = CreateEmptyNode ();
            newNode->parent = link;

            if (link->right == NULL) {
                link->right = newNode;
            } else {
                link->left = newNode;
            }

            link = newNode;

            continue;
        }

        if (strcmp(linesOfText->line[readingLine], "}") == 0) {

            link = link->parent;

            continue;
        }

        link->text = CutBothSides (linesOfText->line[readingLine]);

    }

    newTree->subjects = (Node**) calloc (sizeof(Node*), linesOfText->numberOfLines);
    FillArrayOfSubs (newTree);

    return newTree;
}

bool PutTreeToFile (const char *fileName, Tree* thisTree) {

    FILE *file = fopen (fileName, "wt");

    if ((thisTree == NULL) || (file == NULL)) {
        return false;
    }

    WriteNodeToFile (thisTree->root, file);

    fclose (file);

    return true;
};

void WriteNodeToFile (Node* thisNode, FILE *file) {

    fprintf (file, "\"%s\"\n", thisNode->text);

    if (thisNode->question) {
        fprintf (file, "{\n");
        WriteNodeToFile (thisNode->right, file);
        fprintf (file, "}\n");
    }

    if (thisNode->question) {
        fprintf (file, "{\n");
        WriteNodeToFile (thisNode->left, file);
        fprintf (file, "}\n");
    }
}

char* CutBothSides (char* str) {

    size_t lengthOfStr = 0;
    while (str[lengthOfStr] != '\0') {
        lengthOfStr++;
    }

    char* newStr = (char*) calloc (sizeof(char), lengthOfStr);
    for (size_t pointer = 1; pointer < lengthOfStr - 1; pointer++) {
        newStr[pointer - 1] = str[pointer];
    }

    newStr[lengthOfStr - 1] = '\0';

    return newStr;
}

size_t FillArrayOfSubs (Tree* thisTree) {

    size_t subsLength = 0;
    TryToAddNodeInArrayOfSubs (thisTree, thisTree->root, &subsLength);

    return subsLength;
}

void TryToAddNodeInArrayOfSubs (Tree* thisTree, Node* currentNode, size_t* subsLength) {

    if (currentNode->question) {
        TryToAddNodeInArrayOfSubs (thisTree, currentNode->left,  subsLength);
        TryToAddNodeInArrayOfSubs (thisTree, currentNode->right, subsLength);
    } else {
        thisTree->subjects[*subsLength] = currentNode;
        *subsLength += 1;
    }
}

/*
bool AddNodeInArrayOfSubs (Tree* thisTree, Node* nodeToAdd) {

    size_t pointer = 0;

    //Checking if there is already this node in array
    while (thisTree->subjects[pointer] != nodeToAdd) {

        if (thisTree->subjects[pointer] == NULL) {
            thisTree->subjects[pointer] = nodeToAdd;
            return true;
        }

        pointer++;
    }

    return false;
}
*/

Node** GetWayFromNodeToRoot (Node* thisNode) {

    Node** way  = (Node**) calloc (sizeof(Node*), MAXIMUM_TREE_DEEP);

    Node* link = thisNode;
    size_t pointer = 0;

    while (link != NULL) {
        way[pointer++] = link;
        link = link->parent;
    }

    return way;
}

Node* GetTheFirstSameElement (Node** first, Node** second) {

    size_t pointerFirst  = 0;
    size_t pointerSecond = 0;

    while (first[pointerFirst] != NULL) {
        pointerSecond = 0;
        while (second[pointerSecond] != NULL) {
            if (first[pointerFirst] == second[pointerSecond]) {
                return first[pointerFirst];
            }
            pointerSecond++;
        }
        pointerFirst++;
    }

    return NULL;
}

bool AddNewSub (Node* thisNode, char* newSub, char* newQuestion) {

    thisNode->right = CreateEmptyNode ();
    thisNode->left  = CreateEmptyNode ();

    thisNode->left->text  = thisNode->text;
    thisNode->right->text = newSub;
    thisNode->text        = newQuestion;

    thisNode->left->parent  = thisNode;
    thisNode->right->parent = thisNode;

    thisNode->question = true;

    return true;
}

bool GraphTree (Tree* thisTree) {

    FILE* file = fopen ("dump.txt", "wt");

    if (file == NULL) {
        return false;
    }

    fprintf (file, "digraph Tree {\n");

    GraphNode (thisTree->root, file);

    fprintf(file, "}");

	fclose(file);

    system("dot -Tjpg dump.txt > dump.jpg");
    system("start dump.jpg");

    return true;
}

void GraphNode (Node* thisNode, FILE* file) {

    if (thisNode->question) {

        fprintf(file, "\"%ld\" [shape=\"record\", color=\"#000000\", style=\"filled\", fillcolor=\"#def7fa\", label=\"%s\"]\n",
         thisNode,
         thisNode->text
         );

        GraphNode (thisNode->right, file);
        GraphNode (thisNode->left, file);

        fprintf(file, "\"%ld\":se->\"%ld\"[color=\"green\"];\n",
        thisNode,
        thisNode->right
        );

        fprintf(file, "\"%ld\":sw->\"%ld\"[color=\"red\"];\n",
        thisNode,
        thisNode->left
        );

    } else {

        fprintf(file, "\"%ld\" [shape=\"pentagon\",  color=\"#000000\", style=\"filled\", fillcolor=\"#f5e2d3\", label=\"%s\"]\n",
         thisNode,
         thisNode->text
         );
    }
};

void ConsoleTreeDump (Tree* thisTree) {

    printf("\n\n< < < THIS IS DUMP OF TREE (%ld) > > >\n", thisTree);

    printf("thisTree->wasChanged=%d\n", thisTree);

    ConsoleNodeDump (thisTree->root);

    printf("> > > THIS IS END OF DUMP OF TREE < < <\n");
}

void ConsoleNodeDump (Node* thisNode) {

    printf("THE NODE (%ld) IS QUESTION = %d\n", thisNode, thisNode->question);

    printf("thisNode->text=%s thisNode->parent=%ld thisNode->right=%d thisNode->left=%d\n\n",
            thisNode->text, thisNode->parent, thisNode->right, thisNode->left);

    if (thisNode->question) {
        ConsoleNodeDump (thisNode->right);
        ConsoleNodeDump (thisNode->left);
    }
}
