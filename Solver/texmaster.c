//Version 0.6

#include "texmaster.h"

#define TEX_FILE_NAME "report.tex"

bool WriteBeginning (const char* filename) {

    assert (filename);

    FILE* file = fopen (filename, "w");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\\documentclass[14pt]{article}\n");
    fprintf (file, "\\usepackage{graphicx}\n");
    fprintf (file, "\\usepackage[percent]{overpic}\n");
    fprintf (file, "\\usepackage{hyperref}\n");
    fprintf (file, "\\begin{document}\n");

    fprintf (file, "\\title{                                         \
    This is the beginning of an exciting subtraction of derivatives. \
    Relax and enjoy!}\n");

    fprintf (file, "\\author{By Tuzman Alexander}\n");
    fprintf (file, "\\maketitle\n");

    PicturePic ("pics/begin/head.jpg", file);
    fprintf (file, "\\newline\n");

    fclose (file);

    return true;
}

bool StartOfTakingDerivative (const char* filename, size_t number) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\\section{This is subtraction of %d'st derivative}\n", number);

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
                if (node->value.number != (long long) node->value.number) {
                    fprintf (file, "(%lf)", node->value.number);
                } else {
                    fprintf (file, "(%lld)", (long long) node->value.number);
                }
            } else {
                if (node->value.number != (long long) node->value.number) {
                    fprintf (file, "%lf", node->value.number);
                } else {
                    fprintf (file, "%lld", (long long) node->value.number);
                }
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

void PicturePic (const char* filename, FILE* file) {

    assert (filename);
    assert (file);

    fprintf (file, "\\includegraphics [width=\\textwidth]{%s}\n", filename);

}

void PictureMeme (const char* filename, FILE* file,              \
                size_t Xfirst, size_t Yfirst, DiffNode* first,   \
                size_t Xsecond, size_t Ysecond, DiffNode* second) {

    assert (filename);
    assert (file);

    assert (first);
    assert (second);

    fprintf (file, "\\begin{overpic}[width=\\textwidth]{%s}\n", filename);

    fprintf (file, "\\put (%d,%d) {", Xfirst, Yfirst);
    WriteNode (first, file);
    fprintf (file, "}\n");

    fprintf (file, "\\put (%d,%d) {", Xsecond, Ysecond);
    WriteNode (second, file);
    fprintf (file, "}\n");

    fprintf (file, "\\end{overpic}\n");
}

bool WriteDiff (const char* filename, DiffNode* first, DiffNode* second) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "Let's differentiate \n");
    fprintf (file, "$");
    WriteNode (first, file);
    fprintf (file, "$");
    fprintf (file, "\n\\newline\n");
    fprintf (file, "Now this expression turned into \n");
    fprintf (file, "$");
    WriteNode (second, file);
    fprintf (file, "$");
    fprintf (file, "\n\\newline\n");

    fclose (file);

    return true;
}

bool WriteSimp (const char* filename, DiffNode* first, DiffNode* second) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "Let's make simpler \n");
    fprintf (file, "$");
    WriteNode (first, file);
    fprintf (file, "$");
    fprintf (file, "\n\\newline\n");
    fprintf (file, "Now this expression simpled to \n");
    fprintf (file, "$");
    WriteNode (second, file);
    fprintf (file, "$");
    fprintf (file, "\n\\newline\n");

    fclose (file);

    return true;
}

bool WriteEnd (const char* filename) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\n\nThat is all!\n");
    fprintf (file, "\\newline\n");

    fprintf (file, "\\begin{overpic}[width=\\textwidth]{pics/end/basement.jpg}\n");
    fprintf (file, "\\put (31,20) {\\href{run:https://github.com/Allexande}{\\Large github.com/Allexande}}\n");
    fprintf (file, "\\end{overpic}\n");

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

