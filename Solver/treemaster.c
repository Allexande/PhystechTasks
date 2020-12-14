//Version 0.2

#define RECURRENT_DESCENT_DEBUG

#include "treemaster.h"

DiffTree* CreateNewTree () {

    DiffTree* newTree = (DiffTree*) calloc (sizeof(DiffTree), 1);
    assert   (newTree);

    newTree->root = nullptr;

    return newTree;
}

DiffNode* CreateNewNode (OPnumber newValue, NodeType newType) {

    DiffNode* newDiffNode = (DiffNode*) calloc (sizeof(DiffNode), 1);
    assert   (newDiffNode);

    newDiffNode->type = newType;

    if (newType == CONST) {
        newDiffNode->value.number = newValue;
    }

    if (newType == VAR) {
        newDiffNode->value.var = newValue;
    }

    if (newType == OPERATION) {
        newDiffNode->value.op = (OPnumber) newValue;
    }

    #ifdef RECURRENT_DESCENT_DEBUG
        printf("DEBUG: newDiffNode->value = %d (%lf) (%c)\n", newValue, newValue, newValue);
    #endif

    newDiffNode->left   = nullptr;
    newDiffNode->right  = nullptr;
    newDiffNode->parent = nullptr;

    return newDiffNode;
}

DiffTree* BuildTreeFromFile (const char* fileName) {

    assert (fileName);

    return BuildTreeFromText (ReadTextFromFile (fileName));
}

DiffTree* BuildTreeFromText (const char* text) {

    assert (text);

    #ifdef RECURRENT_DESCENT_DEBUG
        printf("DEBUG: BuildTreeFromText(%s) started\n", text);
    #endif

    DiffTree* newTree = CreateNewTree ();

    size_t position = 0;
    newTree->root = GetGeneral (text, &position);
    assert (newTree->root);

    return newTree;
}

DiffNode* GetGeneral (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetGeneral");
    #endif

    DiffNode* node = GetExpression (str, position);

    if (str[*position] != '\0') {
        SyntaxError (str, position, "Input string do not have \\0 ending");
    }

    return node;
}

DiffNode* GetExpression (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetExpression");
    #endif

    DiffNode* node1 = GetTerm (str, position);

    while (str[*position] == '+' || str[*position] == '-') {

        size_t oldPosition = *position;
        (*position)++;

        DiffNode* node2 = GetTerm (str, position);

        if (str[oldPosition] == '+') {
            node1 = TreeSetNode (node1, node2, OP_ADD, OPERATION);
        } else {
            node1 = TreeSetNode (node1, node2, OP_SUB, OPERATION);
        }
    }

    return node1;
}

DiffNode* GetTerm (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetTerm");
    #endif

    DiffNode* node1 = GetPower (str, position);

    while (str[*position] == '*' || str[*position] == '/') {

        size_t oldPosition = *position;
        (*position)++;

        DiffNode* node2 = GetPower (str, position);

        if (str[oldPosition] == '*') {
            node1 = TreeSetNode (node1, node2, OP_MUL, OPERATION);
        } else {
            node1 = TreeSetNode (node1, node2, OP_DIV, OPERATION);
        }
    }

    return node1;
}

DiffNode* GetPower (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetPower");
    #endif

    DiffNode* node1 = GetPrimaryExpression (str, position);

    while (str[*position] == '^') {

        (*position)++;

        DiffNode* node2 = GetPrimaryExpression (str, position);

        node1 = TreeSetNode (node1, node2, OP_POW, OPERATION);
    }

    return node1;
}

DiffNode* GetPrimaryExpression (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetPrimaryExpression");
    #endif

    if (str[*position] == '(') {

        #ifdef RECURRENT_DESCENT_DEBUG
            printf("DEBUG: In GetPrimaryExpression: str[%d]='(' that is why next called GetExpression \n", *position);
        #endif
        (*position)++;
        DiffNode* node = GetExpression (str, position);

        if (str[*position] != ')') {
            SyntaxError (str, position, "There is no closing bracket");
        }
        (*position)++;

        return node;
    }

    if (isdigit(str[*position])) {
        #ifdef RECURRENT_DESCENT_DEBUG
            printf("DEBUG: In GetPrimaryExpression: str[%d]='number' that is why next called GetNumber \n", *position);
        #endif
        return GetNumber (str, position);
    }

    if ('A' <= str[*position] && 'Z' >= str[*position]) {
        #ifdef RECURRENT_DESCENT_DEBUG
            printf("DEBUG: In GetPrimaryExpression: str[%d]='big letter' that is why next called GetFunction \n", *position);
        #endif
        DiffNode* node = GetFunction (str, position);
        if (node != NULL) {
            return node;
        }
    }

    if ('a' <= str[*position] && 'z' >= str[*position]) {
        #ifdef RECURRENT_DESCENT_DEBUG
            printf("DEBUG: In GetPrimaryExpression: str[%d]='small letter' that is why next called GetVariable \n", *position);
        #endif
        DiffNode* node = GetVariable (str, position);
        if (node != NULL) {
            return node;
        }
    }

    SyntaxError (str, position, "Incorrect primary expression");
}

DiffNode* GetVariable (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetVariable");
    #endif

    DiffNode* node = CreateNewNode ((OPnumber)0, VAR);

    if (isalpha(str[*position])) {
        node->value.var = str[*position];
        (*position)++;
    } else {
        //TODO ”ƒјЋ»“№ node
    }

    return node;
}

DiffNode* GetFunction (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetFunction");
    #endif

    //size_t oldPosition = *position;
    char* funcName = ReadFuncName (str, position);

    DiffNode* node = CreateNewNode ((OPnumber)0, OPERATION);

    if (*funcName == '\0') {
         //TODO раз мы сюда попали может ли быть такое?...
         SyntaxError (str, position, "WTF function does not have name");
         return GetPrimaryExpression (str, position);
    }

    if (str[*position] == '(') {

        #define DEF_FUNCTION(name, number)          \
            if (strcmp(funcName, #name) == 0) {     \
                node->value.op = (OPnumber) number; \
            }

        #include "functions.h"

        #undef DEF_FUNCTION

        if (node->value.op == 0) {
            SyntaxError (str, position, "Unknown function");
        }

        node->right = GetPrimaryExpression (str, position);

        return node;
    }

   SyntaxError (str, position, "No opening bracket after function");
}

DiffNode* GetNumber (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> GetNumber");
    #endif

    DiffNode* node = CreateNewNode ((OPnumber)0, CONST);

    size_t oldPosition = *position;

    while ('0' <= str[*position] && str[*position] <= '9') {
        node->value.number = node->value.number*10 + str[*position] - '0';
        (*position)++;
    }

    if (*position == oldPosition) {
        SyntaxError (str, position, "Number have zero length");
    }

    return node;
}

char* ReadFuncName (const char* str, size_t* position) {

    #ifdef RECURRENT_DESCENT_DEBUG
        ErrorAlert (str, position, "DEBUG: started >>> ReadFuncName");
    #endif

    char*   funcName = (char*) calloc (sizeof(char), strlen (str) - *position);
    assert (funcName);

    size_t localPosition = 0;
    while ('A' <= str[*position] && str[*position] <= 'Z') {
        funcName[localPosition] = str[*position];
        localPosition++;
        (*position)++;
    }

    #ifdef RECURRENT_DESCENT_DEBUG
        printf("DEBUG: ReadFuncName read '%s' \n", funcName);
    #endif

    return funcName;
}
/*
Node* TreeSetNode(Node* addingLeft,    \
                  Node* addingRight,   \
                  number_t addingData,   \
                  char addingType,     \
                  number_t leftData,  \
                  number_t rightData) {

  Node* nodeForAdding = CreateNewNode (addingData, addingType);

  if (leftData == POISON_VALUE_PUSH && rightData == POISON_VALUE_PUSH) {
    nodeForAdding->left  = addingLeft;
    nodeForAdding->right = addingRight;
  }

  if (leftData == POISON_VALUE_PUSH && rightData != POISON_VALUE_PUSH) {
    nodeForAdding->left = addingLeft;
    nodeForAdding->right = CreateNewNode (rightData, TYPE_NUMBER);
  }

  if (leftData != POISON_VALUE_PUSH && rightData == POISON_VALUE_PUSH) {
    nodeForAdding->left = CreateNewNode (leftData, TYPE_NUMBER);
    nodeForAdding->right = addingRight;
  }

  if (leftData != POISON_VALUE_PUSH && rightData != POISON_VALUE_PUSH) {
    nodeForAdding->left  = CreateNewNode (leftData, TYPE_NUMBER);
    nodeForAdding->right = CreateNewNode (rightData, TYPE_NUMBER);
  }

  return nodeForAdding;
} */

DiffNode* TreeSetNode (DiffNode* addingLeft,   \
                       DiffNode* addingRight,  \
                       number_t addingData,    \
                       NodeType addingType) {

    //printf ("GONNA ADD addingData=%d (%lf) (%c)\n", addingData, addingData, addingData);
    //
    //if (addingType == OPERATION) {
    //    addingData = (OPnumber) addingData;
    //}
    //
    //printf ("GONNA ADD addingData=%d (%lf) (%c)\n", addingData, addingData, addingData);

    DiffNode* nodeForAdding = CreateNewNode ((OPnumber)addingData, addingType);

    nodeForAdding->left  = addingLeft;
    nodeForAdding->right = addingRight;

    return nodeForAdding;
}

void SyntaxError (const char* str, const size_t* position, const char* message) {

    printf ("\nAn syntax error on position %d\n", *position);

    ErrorAlert (str, position, message);
}

void LogicError (const char* str, const size_t* position, const char* message) {

    printf ("\nAn logic error on position %d\n", *position);

    ErrorAlert (str, position, message);
}

void ErrorAlert (const char* str, const size_t* position, const char* message) {

    printf ("%s:\n", message);

    size_t localPosition = 0;
    while (str[localPosition] != '\0') {

        if (localPosition == *position) {
            printf (">%c<", str[localPosition]);
        } else {
            printf ("%c", str[localPosition]);
        }

        localPosition++;
    }
}

/*
void DeleteNode (DiffNode* node) {

    if (node != NULL) {

        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        }

        free (node);
    }
}*/

void DeleteChild (DiffNode* node, bool left) {

    assert (node);

    if (left) {
        if (node->left != NULL) {
            free (node->left);
                  node->left = nullptr;
        }
    }

    if (node->right != NULL) {
        free (node->right);
            node->right = nullptr;
    }
}

void DeleteChildren (DiffNode* node) {

    assert (node);

    DeleteChild (node, 1);
    DeleteChild (node, 0);
}

bool TreeDump (DiffTree* tree) {

    assert (tree);

    #ifdef RECURRENT_DESCENT_DEBUG
        printf("TreeDump(%ld) started\n", tree);
    #endif

    FILE* file = fopen ("dump.txt", "wt");

    if (file == NULL) {
        return false;
    }

    fprintf (file, "digraph Tree {\n");
    GraphNode (tree->root, file);
    fprintf(file, "}");

	fclose(file);

    system("dot -Tjpg dump.txt > dump.jpg");
    system("start dump.jpg");

    return true;
}

void GraphNode (DiffNode* thisNode, FILE* file) {

    assert (thisNode);
    assert (file);

    if (thisNode->type == CONST) {
        fprintf(file, "\"%ld\" [shape=\"record\", color=\"#000000\", style=\"filled\", fillcolor=\"#def7fa\", label=\"%lf\"]\n",
        thisNode,
        thisNode->value.number
        );
    }

    if (thisNode->type == VAR) {
        fprintf(file, "\"%ld\" [shape=\"record\", color=\"#000000\", style=\"filled\", fillcolor=\"#def7fa\", label=\"%c\"]\n",
        thisNode,
        thisNode->value.var
        );
    }

    if (thisNode->type == OPERATION) {
        fprintf(file, "\"%ld\" [shape=\"record\", color=\"#000000\", style=\"filled\", fillcolor=\"#def7fa\", label=\"%d\"]\n",
        thisNode,
        thisNode->value.op
        );
    }

    if (thisNode->right != NULL) {
        GraphNode (thisNode->right, file);
    }

    if (thisNode->left != NULL) {
        GraphNode (thisNode->left,  file);
    }

    if (thisNode->right != NULL) {
        fprintf(file, "\"%ld\":se->\"%ld\"[color=\"black\"];\n",
        thisNode,
        thisNode->right
        );
    }

    if (thisNode->left != NULL) {
        fprintf(file, "\"%ld\":sw->\"%ld\"[color=\"black\"];\n",
        thisNode,
        thisNode->left
        );
    }
};
