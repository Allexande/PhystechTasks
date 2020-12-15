//Version 0.5

#include "texmaster.h"

#define TEX_FILE_NAME "report.tex"

bool WriteBeginning (const char* filename) {

    assert (filename);

    FILE* file = fopen (filename, "w");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\\documentclass[14pt]{article}\n");
    fprintf (file, "\\begin{document}\n");
    fprintf (file, "\\title{This is taking derivative !!!}\n");
    fprintf (file, "\\author{Tuzman Alexander}\n");
    fprintf (file, "\\maketitle\n");
    fprintf (file, "Taking derivative can be boring but not with this program!!!\n");
    fprintf (file, "\\newline\\newline \n");

    fclose (file);

    return true;
}

bool StartOfTakingDerivative (const char* filename, size_t number) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\section{This is %d'st derivative}\n", number);

    fclose (file);

    return true;

}

bool WriteSubtree (const char* filename, DiffNode* node) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "$");
    WriteNode (node, file);
    fprintf (file, "$");

    fclose (file);

    return true;
}

void WriteNode (DiffNode* node, FILE* file) {

    assert (file);

    if (node == NULL) {
        return;
    }

    switch (node -> type) {

        case VAR: {
            fprintf (file, "%c", node->value.var);
        } break;

        case CONST: {

            if (node->value.number < 0) {
                fprintf (file, "(%lf)", node->value.number);
            } else {
                fprintf (file, "%lf", node->value.number);
            }

        } break;


        case OPERATION: {

            switch (node->value.op) {

                case OP_ADD: {
                    WriteNode (node->left, file);
                    fprintf (file, "+");
                    WriteNode (node->right, file);
                } break;

                case OP_SUB: {
                    WriteNode (node->left, file);
                    fprintf (file, "-");
                    WriteNode (node->right, file);
                } break;

                case OP_MUL: {

                    if (node->left->type == OPERATION &&
                       (node->left->value.op == OP_ADD || node->left->value.op == OP_SUB)) {
                        WriteInRound(node -> left, file);
                    } else {
                        WriteNode (node->left, file);
                    }

                    fprintf (file, "\\cdot ");

                    if (node->right->type == OPERATION &&
                       (node->right->value.op == OP_ADD || node->right->value.op == OP_SUB)) {
                        WriteInRound (node->right, file);
                    } else {
                        WriteNode (node->right, file);
                    }

                } break;

                case OP_DIV: {
                    fprintf (file, "\\frac ");
                    WriteInBraces (node->left, file);
                    WriteInBraces (node->right, file);
                } break;

                case OP_POW: {

                    if (node->left->type == CONST || node->left->type == VAR) {
                      WriteNode (node->left, file);
                    } else {
                      WriteInRound (node->left, file);
                    }

                    fprintf(file, "^");
                    WriteInBraces (node->right, file);

                } break;

                case OP_LGN: {
                    fprintf (file, "\\ln ");
                    WriteInRound (node->left, file);
                } break;

                case OP_EXP: {
                    fprintf (file, "e^");
                    WriteInBraces (node->left, file);
                } break;

                case OP_SIN: {
                    fprintf (file, "\\sin ");
                    WriteInRound (node->left, file);
                } break;

                case OP_COS: {
                    fprintf (file, "\\cos ");
                    WriteInRound (node->left, file);
                } break;

                case OP_TAN: {
                    fprintf (file, "\\tan ");
                    WriteInRound (node->left, file);
                } break;

                case OP_CTN: {
                    fprintf (file, "\\cot ");
                    WriteInRound (node->left, file);
                } break;

                case OP_SRT: {
                    fprintf (file, "\\sqrt ");
                    WriteInRound (node->left, file);
                } break;

                case OP_ASN: {
                    fprintf (file, "\\arcsin ");
                    WriteInRound (node->left, file);
                } break;

                case OP_ACS: {
                    fprintf (file, "\\arccos ");
                    WriteInRound (node->left, file);
                } break;

                case OP_ATN: {
                    fprintf (file, "\\arctan ");
                    WriteInRound (node->left, file);
                } break;

                /*case OP_ACN: {
                    fprintf (file, "\\arcñtan ");
                    WriteInRound (node->left, file);
                } break; */

                case OP_SIH: {
                    fprintf (file, "\\sinh ");
                    WriteInRound (node->left, file);
                } break;

                case OP_COH: {
                    fprintf (file, "\\cosh ");
                    WriteInRound (node->left, file);
                } break;

                case OP_TGH: {
                    fprintf (file, "\\tanh ");
                    WriteInRound (node->left, file);
                } break;
            }

    } break;

    default: {
        fprintf (file, "(Unknown node type %d)", node->type);
    } break;

  }
}

void WriteInRound (DiffNode* node, FILE* file) {

    fprintf (file, "(");
    WriteNode (node, file);
    fprintf (file, ")");
}

void WriteInBraces (DiffNode* node, FILE* file) {

    fprintf (file, "{");
    WriteNode (node, file);
    fprintf (file, "}");
}

bool WriteEnd (const char* filename) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\n\nThat is all!\n");
    fprintf (file, "\section{Author's GitHub:}\n");
    fprintf (file, "\href{https://github.com/Allexande}{Allexande}\n");
    fprintf (file, "\\end{document}\n");

    fclose (file);

    return true;
}

bool TranslateToPDF (const char* filename) {

    assert (filename);

    size_t length1 = strlen ("pdflatex ");
    size_t length2 = strlen (filename);

    char*   request = (char*) calloc (sizeof(char), length1 + length2 + 1);
    assert (request);

    memcpy (request, "pdflatex ", length1);
    memcpy (request + length1, filename, length2 + 1);

    system (request);

    return true;
}

