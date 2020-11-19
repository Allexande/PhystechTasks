//Version 0.2

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

    return newTree;
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

    return true;
}

void GraphNode (Node* thisNode, FILE* file) {

    if (thisNode->question) {
        fprintf(file, "\"%ld\" [shape=\"record\", fillcolor=\"#AFEEEE\", label=\"%s\"]\n", thisNode, thisNode->text);
        GraphNode (thisNode->right, file);
        GraphNode (thisNode->left, file);
        fprintf(file, "\"%ld\":se->\"%ld\"[color=\"#011504\", label=\"yes\"];\n", thisNode, thisNode->right);
        fprintf(file, "\"%ld\":sw->\"%ld\"[color=\"#011504\", label=\"no\"];\n", thisNode, thisNode->left);
    } else {
        fprintf(file, "\"%ld\" [shape=\"pentagon\", fillcolor=\"#AFEEEE\", label=\"%s\"]\n", thisNode, thisNode->text);
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
