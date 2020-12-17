//Version 0.7

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
    fprintf (file, "\\usepackage[bottom=0.5in,top=0.8in, left=0.8in, right=0.8in]{geometry}\n");
    fprintf (file, "\\begin{document}\n");

    fprintf (file, "\\title{                                         \
    This is the beginning of an exciting subtraction of derivatives. \
    Relax and enjoy!}\n");

    fprintf (file, "\\author{By Tuzman Alexander}\n");
    fprintf (file, "\\maketitle\n");

    PicturePic ("pics/begin/head.jpg", file);
    fprintf (file, "\\pagebreak\n");

    fclose (file);

    SetRandSeed ();

    return true;
}

bool StartOfTakingDerivative (const char* filename, size_t number) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "\\section{This is subtraction of %d'st derivative}\n", number);
    fprintf (file, "\\LARGE\n");

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
                    WriteInRound (node->right, file);
                } break;

                case OP_COS: {
                    fprintf (file, "\\cos ");
                    WriteInRound (node->right, file);
                } break;

                case OP_TAN: {
                    fprintf (file, "\\tan ");
                    WriteInRound (node->right, file);
                } break;

                case OP_CTN: {
                    fprintf (file, "\\cot ");
                    WriteInRound (node->right, file);
                } break;

                case OP_SRT: {
                    fprintf (file, "\\sqrt ");
                    WriteInRound (node->right, file);
                } break;

                case OP_ASN: {
                    fprintf (file, "\\arcsin ");
                    WriteInRound (node->right, file);
                } break;

                case OP_ACS: {
                    fprintf (file, "\\arccos ");
                    WriteInRound (node->right, file);
                } break;

                case OP_ATN: {
                    fprintf (file, "\\arctan ");
                    WriteInRound (node->right, file);
                } break;

                /*case OP_ACN: {
                    fprintf (file, "\\arcñtan ");
                    WriteInRound (node->left, file);
                } break; */

                case OP_SIH: {
                    fprintf (file, "\\sinh ");
                    WriteInRound (node->right, file);
                } break;

                case OP_COH: {
                    fprintf (file, "\\cosh ");
                    WriteInRound (node->right, file);
                } break;

                case OP_TGH: {
                    fprintf (file, "\\tanh ");
                    WriteInRound (node->right, file);
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

bool WriteText (const char* filename, const char* text) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    fprintf (file, "%s\n", text);

    fclose (file);

    return true;

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
    fprintf (file, "\\fbox{\\parbox{260px}{\\begin{center}$");
    WriteNode (first, file);
    fprintf (file, "$\\end{center}}}}\n");

    fprintf (file, "\\put (%d,%d) {", Xsecond, Ysecond);
    fprintf (file, "\\fbox{\\parbox{260px}{\\begin{center}$");
    WriteNode (second, file);
    fprintf (file, "$\\end{center}}}}\n");

    fprintf (file, "\\end{overpic}\n");
    fprintf (file, "\\pagebreak\n");
    fprintf (file, "\\break\n");
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

    PostMeme (file, 1, first, second);

    fclose (file);

    return true;
}

bool WriteSimp (const char* filename, DiffNode* first, DiffNode* second) {

    assert (filename);

    FILE* file = fopen (filename, "a");
    if (file == NULL) {
        return false;
    }

    if (!AreTheSameSubtrees (first, second)) {

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

        PostMeme (file, 0, first, second);
    }

    fclose (file);

    return true;
}

bool PostMeme (FILE* file, bool isDiffMeme, DiffNode* first, DiffNode* second) {

    int rand;
    if (isDiffMeme) {
        rand = GeterateRandomInt (1, DIFF_MEMES_NUMBER + 1);
    } else {
        rand = GeterateRandomInt (1, SIMP_MEMES_NUMBER + 1);
    }

    char* pathname;
    if (isDiffMeme) {
        pathname = "pics/diff/";
    } else {
        pathname = "pics/simp/";
    }

    #define MEME(                     \
      isDiff,                         \
      filename,                       \
      number,                         \
      Xfirst,                         \
      Yfirst,                         \
      Xsecond,                        \
      Ysecond)                        \
        if (isDiff == isDiffMeme &&   \
            number == rand) {         \
                                      \
            PictureMeme (             \
                UniteStrings (        \
                    pathname,        \
                    #filename          \
                ),                    \
                file,                 \
                Xfirst,               \
                Yfirst,               \
                first,                \
                Xsecond,              \
                Ysecond,              \
                second                \
                );                    \
                                      \
            return true;              \
        }

    #include "memes.h"

    #undef MEME

    return false;
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

/*
void TranslateToPDF (const char* filename) {

    assert (filename);

    system (UniteStrings ("pdflatex ", filename));
}
*/

char* UniteStrings (char* first,  char* second) {

    assert (first);
    assert (second);

    char*   result = (char*) calloc (sizeof(char), strlen (first) + strlen (second) + 1);
    assert (result);

    strcpy (result, first);
    strcat (result, second);

    return result;
}

/*
char* UniteStrings (char* first,  char* second) {

    assert (first);
    assert (second);

    printf("1)UniteStrings(%s, %s) started\n", first, second);
//printf ("-------> first=%s first[0]=%c (%d)", first, first[0], first[0]);
    size_t length1 = strlen (first)+1; //printf("length1=%d\n", length1);
    size_t length2 = strlen (second);//printf("length2=%d\n", length2);
//printf("NOW UniteStrings(%s, %s)\n", first, second);
    printf("2)UniteStrings(%s, %s) started first=%ld\n", first, second, first);

    char*   result = (char*) calloc (sizeof(char), length1 + length2 + 1);
    assert (result);
    printf("3)UniteStrings(%s, %s) started first=%ld\n", first, second, first);
    for (; 0; ) {
        printf("test)UniteStrings(%s, %s) started first=%ld\n", first, second, first);
    }
    /*
    printf("> > BEFORE MEMCOPY result=%s\n", result);
    memcpy (result, first, length1);
    printf("> > AFTER 1 MEMCOPY result=%s\n", result);
    memcpy (result + length1, second, length2 + 1);

    printf("> > AFTER 2 MEMCOPY result=%s\n", result);

//printf("> > BEFORE MEMCOPY result=%s\n", result);
    //for (size_t firstPointer = 0; firstPointer < length1; firstPointer++) {
//printf("first[%d]=%c(%d)\n", firstPointer, first[firstPointer], first[firstPointer]);
//printf("first[%d]=%c(%d)\n", firstPointer-1, first[firstPointer-1], first[firstPointer-1]);
//printf("4.%d)UniteStrings(%s, %s) started\n", firstPointer*2, first, second);
        //result[firstPointer] = first[firstPointer];
//printf("4.%d)UniteStrings(%s, %s) started\n", firstPointer*2+1, first, second);
    //}

//printf ("-------> first=%s first=%c (%d)", first, first, first);

//printf("> > AFTER 1 MEMCOPY result=%s\n", result);
    for (size_t secondPointer = length1; secondPointer < length1 + length2 + 1; secondPointer++) {
//printf("second[%d]=%c(%d)\n", secondPointer - length1, second[secondPointer - length1], second[secondPointer - length1]);
        printf("5.%d)UniteStrings(%s, %s) started first=%ld\n", secondPointer*2, first, second, first);
        result[secondPointer] = second[secondPointer - length1];
        printf("5.%d)UniteStrings(%s, %s) started\n", secondPointer*2+1, first, second);
    }
//printf("> > AFTER 2 MEMCOPY result=%s\n", result);
printf("NOW UniteStrings(%s, %s)\n", first, second);
    return result;
} */



char* IntToString (int numToConvert) {

    char str[DIFF_MEMES_NUMBER + SIMP_MEMES_NUMBER];
    sprintf (str, "%d\0", numToConvert);

    return str;
}

