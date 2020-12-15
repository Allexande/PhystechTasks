//Version 0.3

//Every rule have special structure:
//SIMPLIFICATION_RULE(condition, action)

SIMPLIFICATION_RULE(                     \
                                         \
    node->left != NULL              &&   \
    node->left->type == CONST       &&   \
    node->right != NULL             &&   \
    node->right->type == CONST           \
,                                        \
    switch (node->value.op) {            \
                                         \
        case OP_ADD: {                   \
            SimplifyADD (node);          \
        } break;                         \
                                         \
        case OP_SUB: {                   \
            SimplifySUB (node);          \
        } break;                         \
                                         \
        case OP_MUL: {                   \
            SimplifyMUL (node);          \
        } break;                         \
                                         \
        case OP_DIV: {                   \
            SimplifyDIV (node);          \
        } break;                         \
                                         \
        case OP_POW: {                   \
            SimplifyPOW (node);          \
        } break;                         \
                                         \
    }                                    \
)

SIMPLIFICATION_RULE(                     \
                                         \
    node->left == NULL              &&   \
    node->right != NULL             &&   \
    node->right->type == CONST           \
,                                        \
    switch (node->value.op) {            \
                                         \
        case OP_ABS: {                   \
            SimplifyABS (node);          \
        } break;                         \
                                         \
        case OP_LGN: {                   \
            SimplifyLGN (node);          \
        } break;                         \
                                         \
        case OP_EXP: {                   \
            SimplifyEXP (node);          \
        } break;                         \
                                         \
        case OP_SRT: {                   \
            SimplifySRT (node);          \
        } break;                         \
                                         \
        case OP_SIN: {                   \
            SimplifySIN (node);          \
        } break;                         \
                                         \
        case OP_COS: {                   \
            SimplifyCOS (node);          \
        } break;                         \
                                         \
        case OP_TAN: {                   \
            SimplifyTAN (node);          \
        } break;                         \
                                         \
        case OP_CTN: {                   \
            SimplifyCTN (node);          \
        } break;                         \
                                         \
        case OP_ASN: {                   \
            SimplifyASN (node);          \
        } break;                         \
                                         \
        case OP_ACS: {                   \
            SimplifyACS (node);          \
        } break;                         \
                                         \
        case OP_ATN: {                   \
            SimplifyATN (node);          \
        } break;                         \
                                         \
        case OP_ACN: {                   \
            SimplifyACN (node);          \
        } break;                         \
                                         \
        case OP_SIH: {                   \
            SimplifySIH (node);          \
        } break;                         \
                                         \
        case OP_COH: {                   \
            SimplifyCOH (node);          \
        } break;                         \
                                         \
        case OP_TGH: {                   \
            SimplifyTGH (node);          \
        } break;                         \
                                         \
        case OP_CTH: {                   \
            SimplifyCTH (node);          \
        } break;                         \
                                         \
    }                                    \
)

SIMPLIFICATION_RULE(                     \
                                         \
   (node->left != NULL              &&   \
    node->left->type == CONST       &&   \
    node->left->value.number == 0   &&   \
    node->right != NULL             ||   \
    node->right != NULL             &&   \
    node->right->type == CONST      &&   \
    node->right->value.number == 0  &&   \
    node->left != NULL)             &&   \
   (node->value.op == OP_MUL        ||   \
    node->value.op == OP_DIV)            \
,                                        \
    node->type = CONST;                  \
    node->value.number = 0;              \
    DeleteChildren (node);               \
)

SIMPLIFICATION_RULE(                     \
                                         \
   (node->right != NULL             &&   \
    node->right->type == CONST      &&   \
    node->right->value.number == 0  &&   \
    node->left != NULL)             &&   \
   (node->value.op == OP_ADD        ||   \
    node->value.op == OP_SUB)            \
,                                        \
    if (parent != NULL) {                \
        if (parent->left == node) {      \
            parent->left = (node->left); \
        } else {                         \
            parent->right = (node->left);\
        }                                \
    }                                    \
                                         \
)

SIMPLIFICATION_RULE(                     \
                                         \
   (node->left != NULL             &&    \
    node->left->type == CONST      &&    \
    node->left->value.number == 0  &&    \
    node->right != NULL)           &&    \
   (node->value.op == OP_ADD       ||    \
    node->value.op == OP_SUB)            \
,                                        \
                                         \
    if (parent != NULL) {                \
        if (parent->left == node) {      \
            parent->left = (node->right);\
        } else {                         \
            parent->right =(node->right);\
        }                                \
    }                                    \
)


SIMPLIFICATION_RULE(                     \
                                         \
    node->right != NULL             &&   \
    node->right->type == CONST      &&   \
    node->left != NULL              &&   \
    node->value.op == OP_POW        &&   \
   (node->right->value.number == 0  ||   \
    node->right->value.number == 1)      \
,                                        \
    if (node->right->value.number == 0) {\
        node->type = CONST;              \
        node->value.number = 1;          \
        DeleteChildren (node);           \
    } else {                             \
                                         \
    if (parent != NULL) {                \
        if (parent->left == node) {      \
            parent->left = (node->left); \
        } else {                         \
            parent->right =(node->left); \
        }                                \
    }                                    \
                                         \
    }                                    \
)

SIMPLIFICATION_RULE(                     \
                                         \
    node->right != NULL             &&   \
    node->right->type == CONST      &&   \
    node->left != NULL              &&   \
    node->value.op == OP_POW        &&   \
    node->left->value.number == 0        \
,                                        \
    node->type = CONST;                  \
    node->value.number = 0;              \
    DeleteChildren (node);               \
)
