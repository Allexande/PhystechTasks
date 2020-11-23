//Version 1.6.1

#include "list.h"

//Consts

#define POISON 30234

//Flags

#define WARNINGS

//#define LIST_DEBUG

//Defines for working with list

#define NEXT(pointer) thisList->next[pointer]
#define PREV(pointer) thisList->prev[pointer]
#define DATA(pointer) thisList->data[pointer]

#define HEAD thisList->head
#define TAIL thisList->tail
#define FREE thisList->free

#define LENGTH   thisList->length
#define CAPACITY thisList->capacity

#define LINEAR thisList->linear

List* ListConstruct (size_t capacity) {

    List* thisList = (List*) calloc (sizeof(List), 1);
    assert (thisList);

    thisList->data = (elem_t*) calloc (sizeof(elem_t), capacity + 1);
    assert (thisList->data);
    thisList->next = (index_t*) calloc (sizeof(index_t), capacity + 1);
    assert (thisList->next);
    thisList->prev = (index_t*) calloc (sizeof(index_t), capacity + 1);
    assert (thisList->prev);

    HEAD = 1;
    TAIL = 1;
    FREE = 1;

    LENGTH   = 0;
    CAPACITY = capacity;

    LINEAR = true;

    DATA(0) = POISON;

    for (size_t point = 1; point <= capacity; point++) {

        DATA(point) = POISON;
		PREV(point) = 0;
		NEXT(point) = point + 1;

    }

    NEXT(capacity) = 0;

    ASSERT_OK(thisList)

    return thisList;
};

index_t GetHead (List* thisList) {

    ASSERT_OK(thisList)

    return HEAD;

};

index_t GetTail (List* thisList) {

    ASSERT_OK(thisList)

    return TAIL;

};

index_t GetLenght (List* thisList) {

    ASSERT_OK(thisList)

    return LENGTH;

};

index_t GetCapacity (List* thisList) {

    ASSERT_OK(thisList)

    return CAPACITY;

};

index_t GetIndexFromOrder (List* thisList, index_t number) {

    ASSERT_OK(thisList)

	if (number > LENGTH) {
        return 0;

    }

    if (LINEAR) {
        return number;

    }

    index_t indexToFind = HEAD;

	for (index_t point = 1; point < number; point++) {

        if (point > LENGTH) {
            return 0;

        }

		indexToFind = NEXT(indexToFind);
	}

    #ifdef WARNINGS
        printf ("WARNING!                                                                    \n"
                "You have just got physical adress of the node from it's logical position.   \n"
                "It was a long operation with O(N) asymptotic.                               \n"
        );
    #endif

	return indexToFind;
};

bool ListMakeLinear (List** thisList) {

    ASSERT_OK(*thisList)

    if ((*thisList)->linear) {
        return false;

    }

    List* LinearList = ListConstruct ((*thisList)->capacity);

    index_t link = (*thisList)->head;

    for(index_t point = 1; point <= (*thisList)->length; point++) {

        LinearList->data[point] = (*thisList)->data[link];
        LinearList->next[point] = point + 1;
        LinearList->prev[point] = point - 1;
        LinearList->length++;
        link = (*thisList)->next[link];

    }

    ListDestroy (*thisList);

    *thisList = LinearList;

    (*thisList)->head = 1;
    (*thisList)->tail = (*thisList)->length;
    (*thisList)->free = (*thisList)->length + 1;
    (*thisList)->linear = true;

    ConsoleDump (*thisList);

    #ifdef WARNINGS
        printf ("WARNING!                                                          \n"
                "You have just brought physical addresses to logical addresses.    \n"
                "It was a long operation with O(N) asymptotic.                     \n"
        );
    #endif

    return true;
};

bool TryToRealloc (List* thisList) {

    if (LENGTH >= CAPACITY) {

        thisList->data = (elem_t*)  realloc (thisList->data, sizeof(elem_t)  * CAPACITY * REALLOC_UP + 1);
        assert(thisList->data);
        thisList->next = (index_t*) realloc (thisList->next, sizeof(index_t) * CAPACITY * REALLOC_UP + 1);
        assert(thisList->next);
        thisList->prev = (index_t*) realloc (thisList->prev, sizeof(index_t) * CAPACITY * REALLOC_UP + 1);
        assert(thisList->prev);

        FREE = CAPACITY;

		for (index_t point = CAPACITY; point <= CAPACITY * REALLOC_UP; point++) {
            thisList->data[point] = POISON;
			thisList->next[point] = point + 1;
			thisList->prev[point] = 0;
		}

		CAPACITY *= REALLOC_UP;

        NEXT(CAPACITY) = 0;

        #ifdef WARNINGS
            printf("WARNING!                          \n"
                   "You have just realloced the list. \n"
                   "It was a long operation.          \n"
            );
        #endif

        return true;

    }

    return false;
};

bool ListDestroy (List* thisList) {

    if (thisList == NULL) {
        return false;
    }

    free(thisList->data);
         thisList->data = nullptr;

    free(thisList->next);
         thisList->next = nullptr;

    free(thisList->prev);
         thisList->prev = nullptr;

    free(thisList);
         thisList = nullptr;

    return true;
};

index_t ListInsertAtIndex (List* thisList, elem_t newElem, index_t index) {

    ASSERT_OK(thisList)

    LINEAR = false;

	if (index == 0) {
		return ListInsertBegin (thisList, newElem);

	}

	index_t nextIndex = GetIndexFromOrder (thisList, index);

    return ListInsertAtPlace (thisList, newElem, nextIndex);
};

index_t ListInsertAfterIndex (List* thisList, elem_t newElem, index_t index) {

    ASSERT_OK(thisList)

	return ListInsertAtIndex (thisList, newElem, index);
};

index_t ListInsertBeforeIndex (List* thisList, elem_t newElem, index_t index) {

    ASSERT_OK(thisList)

	return ListInsertAtIndex (thisList, newElem, --index);
};

index_t ListInsertBegin (List* thisList, elem_t newElem) {

    ASSERT_OK(thisList)

    LINEAR = false;

	LENGTH++;

	TryToRealloc(thisList);

	index_t insertedIndex = FREE;
    FREE = NEXT(FREE);

	PREV(HEAD) = insertedIndex;

	DATA(insertedIndex) = newElem;
	NEXT(insertedIndex) = HEAD;
	PREV(insertedIndex) = 0;

	HEAD = insertedIndex;

	#ifdef LIST_DEBUG
        printf("DEBUG: After calling ListInsertBegin(thisList, %d):\n", newElem);
        //ConsoleDump (thisList);
        ConsoleData   (thisList);
	#endif

	return insertedIndex;
};

index_t ListInsertEnd (List* thisList, elem_t newElem) {

    ASSERT_OK(thisList)

	LENGTH++;

	TryToRealloc(thisList);

	index_t insertedIndex = FREE;
    FREE = NEXT(FREE);

	NEXT(TAIL) = insertedIndex;

	DATA(insertedIndex) = newElem;
	NEXT(insertedIndex) = 0;
	PREV(insertedIndex) = TAIL;

	TAIL = insertedIndex;

	#ifdef LIST_DEBUG
        printf("DEBUG: After calling ListInsertEnd(thisList, %d):\n", newElem);
        //ConsoleDump (thisList);
        ConsoleData   (thisList);
	#endif

	return insertedIndex;
};

index_t ListInsertAtPlace (List* thisList, elem_t newElem, index_t place) {

    if (place == TAIL) {
		return ListInsertEnd(thisList, newElem);

	}

    //??
	if (place == 1) {
        return ListInsertBegin(thisList, newElem);

	}

	if (place > CAPACITY || DATA(place) == POISON) {
        return 0;

	}

	LENGTH++;

	TryToRealloc (thisList);

	LINEAR = false;

	index_t insertedIndex = FREE;
    FREE = NEXT(FREE);

	PREV(insertedIndex) = place;
	NEXT(insertedIndex) = NEXT(place);

	PREV(NEXT(insertedIndex)) = insertedIndex;
	NEXT(place) = insertedIndex;

	DATA(insertedIndex) = newElem;

	#ifdef LIST_DEBUG
        printf("DEBUG: After calling ListInsertAtPlace(thisList, %d, %d):\n", newElem, place);
        //ConsoleDump (thisList);
        ConsoleData   (thisList);
	#endif

	    printf("END OF FUNCTION thisList->length=%d\n", thisList->length);


	return place;
};

index_t ListEraseAtIndex (List* thisList, index_t index) {

    ASSERT_OK(thisList)

    if (index > LENGTH) {
        return 0;

    }

    LINEAR = false;

    index = GetIndexFromOrder (thisList, index);

	return ListEraseAtPlace (thisList, index);
};

index_t ListEraseFromBegin (List* thisList) {

    index_t elem = NEXT(HEAD);

	bool result = ListEraseAtIndex(thisList, 1);
	HEAD = elem;

    return result;
};

index_t ListEraseFromEnd (List* thisList) {

    index_t elem = PREV(TAIL);

    bool result = ListEraseAtIndex(thisList, LENGTH);
    TAIL = elem;

    return result;
};

index_t ListEraseAtPlace (List* thisList, index_t place) {

    LENGTH--;

    LINEAR = false;

    PREV(NEXT(place)) = PREV(place);
    NEXT(PREV(place)) = NEXT(place);

    DATA(place) = POISON;
    NEXT(place) = FREE;
    PREV(place) = 0;

    FREE = place;

    #ifdef LIST_DEBUG
        printf("DEBUG: After calling ListEraseAtPlace (thisList, %d):\n", place);
        //ConsoleDump (thisList);
        ConsoleData   (thisList);
	#endif

    return place;
};


elem_t ListGetByOrder (List* thisList, index_t order) {

    ASSERT_OK(thisList)

    if (order > LENGTH) {
        return POISON;

    }

    if (LINEAR) {
        return DATA(order);

    }

    index_t link = HEAD;

    for (index_t point = 1; point <= order; point++) {
        link = NEXT(link);
    }

    #ifdef WARNINGS
        printf ("WARNING!                                                         \n"
                "You have just got data of the node from it's logical position.   \n"
                "It was a long operation with O(N) asymptotic.                    \n"
        );
    #endif

    return DATA(link + 1);
};

elem_t ListGetByIndex (List* thisList, index_t index) {

    ASSERT_OK(thisList)

    if (index < 1 || index > CAPACITY) {
        return POISON;

    }

    return DATA(index - 1);
};

bool ListContains (List* thisList, elem_t element) {

    index_t link = HEAD;

    for (index_t point = 0;  point <= LENGTH; point++) {
        if(DATA(link) == element) {
            return true;

        }

        link = NEXT(link);
    }

     #ifdef WARNINGS
        printf ("WARNING!                                                                  \n"
                "You have just checked if there is a node with certain data in the list.   \n"
                "It was a long operation with O(N) asymptotic.                             \n"
        );
    #endif

    return false;
};

char* DeleteRepetitiveSymbols (char* str, char symbol, size_t limit) {

    assert(str);

    char* newStr = (char*) calloc (sizeof(char), strlen(str));
    assert(newStr);

    size_t pointerStr = 0;
    size_t pointerNew = 0;

    size_t recentCount = 0;

    do {

        if (str[pointerStr] == symbol) {
            recentCount++;
            if (recentCount > limit) {
                pointerStr++;
                continue;
            }
        } else {
            recentCount = 0;
        }

        newStr[pointerNew] = str[pointerStr];
        pointerNew++;
        pointerStr++;

    } while (str[pointerStr] != '\0');

    return newStr;
};

char* DeleteExcessSpaces (char* str) {
    return DeleteRepetitiveSymbols (str, ' ', 1);
};

bool HTMLList (List* thisList) {
    FILE* file = fopen ("list.js", "w");

    if (file == NULL) {
        return false;

    }

    //Adding JS command which will insert code from list.js to body of HTMLdump.html
    fprintf (file, "document.body.innerHTML = '");

    //Adding beginning of table and beginning (title) of first column
    fprintf (file, DeleteExcessSpaces ("<table>                                         \
                        <tr>                                                            \
                            <td>                                                        \
                                <p>                                                     \
                                    List of nodes in order they are located in memory:  \
                                </p>                                                    \
            "));

    for (index_t point = 0; point < CAPACITY; point++) {

        if (DATA(point) != POISON) {

            //Adding a usual node in first column
            fprintf (file, DeleteExcessSpaces ("<div class=\"node\" id=\"%d\">                            \
                                <center class=\"adress\">%d</center>                                      \
                                    <div class=\"container\">                                             \
                                        <div class=\"info\">                                              \
                                            <div class=\"data field\">%d</div>                            \
                                            <div class=\"next field\" onclick=\"Conduct(%d)\">%d</div>    \
                                            <div class=\"prev field\" onclick=\"Conduct(%d)\">%d</div>    \
                                        </div>                                                            \
                                    </div>                                                                \
                                </div>"),
            point,
            DATA(point),
            point,
            NEXT(point),
            NEXT(point),
            PREV(point),
            PREV(point));

        } else {

            //Adding a free node in first column
            fprintf (file, DeleteExcessSpaces ("<div class=\"node\" style=\"background:yellow\">      \
                                <center class=\"adress\">%d [FREE]</center>                           \
                                    <div class=\"container\">                                         \
                                        <div class=\"info\">                                          \
                                            <div class=\"data field\">%d</div>                        \
                                            <div class=\"next field\">%d</div>                        \
                                            <div class=\"prev field\">%d</div>                        \
                                        </div>                                                        \
                                    </div>                                                            \
                                </div>"),
            DATA(point),
            point,
            NEXT(point),
            PREV(point));

        }
    }

    //Adding ending of first column and beginning (title) of second column and first node "HEAD"
    fprintf (file, DeleteExcessSpaces ("</td>                                                               \
                    <td style=\"border-left: 1px solid Aquamarine; border-right: 1px solid Aquamarine;\">   \
                        <p>                                                                                 \
                            List of nodes in order they are linked between each other:                      \
                        </p>                                                                                \
                        <div class=\"node\" style=\"background:Orange\">HEAD</div>                          \
                        <center>                                                                            \
                            <i class=\"up\"></i>                                                            \
                                                                                                            \
                            <i class=\"down\"></i>                                                          \
                        </center>                                                                           \
            "));

    index_t link = HEAD;

    for(index_t point = 1; point <= LENGTH; point++) {

        //Adding a node in second column
        fprintf (file, DeleteExcessSpaces ("<div class=\"node\">                  \
                            <center class=\"adress\">%d</center>                  \
                            <div class=\"container\">                             \
                                <div class=\"info\">                              \
                                    <div class=\"data field\">%d</div>            \
                                    <div class=\"next field\">%d</div>            \
                                    <div class=\"prev field\">%d</div>            \
                                </div>                                            \
                            </div>                                                \
                        </div>                                                    \
                        <center>                                                  \
                            <i class=\"up\"></i>                                  \
                                                                                  \
                            <i class=\"down\"></i>                                \
                        </center>"),
        DATA(link),
        link,
        NEXT(link),
        PREV(link));

        link = NEXT(link);

    }

    //Adding ending of second column and beginning (title) of third column
    fprintf (file, DeleteExcessSpaces ("<div class=\"node\" style=\"background:Orange\">              \
                        TAIL                                                                          \
                    </div>                                                                            \
                </td>                                                                                 \
                <td style=\"position:fixed\">                                                         \
                    <p>                                                                               \
                        This is dump of special list.                                                 \
                    </p>                                                                              \
                    <div class=\"node\">                                                              \
                        <center class=\"adress\">                                                     \
                            DATA                                                                      \
                        </center>                                                                     \
                        <div class=\"container\">                                                     \
                            <div class=\"info\">                                                      \
                                <div class=\"data field\">                                            \
                                    POSITION                                                          \
                                </div>                                                                \
                                <div class=\"next field\">                                            \
                                    NEXT                                                              \
                                </div>                                                                \
                                <div class=\"prev field\">                                            \
                                    PREV                                                              \
                                </div>                                                                \
                            </div>                                                                    \
                        </div>                                                                        \
                    </div>                                                                            \
    <p>                                                                                               \
        POSITION - the physical position of node in array in memory                                   \
        <br>DATA - the value which the node keeps                                                     \
        <br>NEXT - the pointer on physical position of next node                                      \
        <br>PREV - the pointer on physical position of previous node                                  \
        <br>Free nodes have value which is equal to POISON (%d)                                       \
        <br><br>HEAD = %d                                                                             \
        <br>TAIL = %d                                                                                 \
        <br>FREE = %d                                                                                 \
        <br>LENGTH = %d                                                                               \
        <br>CAPACITY = %d                                                                             \
        <br>LINEAR = %d                                                                               \
        </p>"),
    POISON,
    HEAD,
    TAIL,
    FREE,
    LENGTH,
    CAPACITY,
    LINEAR
    );

    //Adding the end of JS command
    fprintf (file, "';");

	fclose (file);

    return true;
};

bool ListGraphPhysical (List* thisList) {

    FILE* file = fopen ("PhysicalDump.txt", "wt");

    if (file == NULL) {
        return false;
    }

    fprintf (file, "digraph MyGraph {\n");
	fprintf (file, "node [shape=\"record\", style=\"filled\", color=\"#008000\", fillcolor=\"#C0FFC0\"];\n");

    fprintf (file, "\"%d\" [color=\"#000080\", fillcolor=\"#FFA500\", label=\"{HEAD}\"];\n", -2);
    fprintf (file, "\"%d\" [color=\"#000080\", fillcolor=\"#FFA500\", label=\"{TAIL}\"];\n", -3);

    for (index_t point = 1; point <= CAPACITY; point++) {
        if (DATA(point) != POISON) {
            fprintf(file, "\"%d\" [fillcolor=\"#AFEEEE\", label=\"{%d|{%d|%u|%d}}\"]\n",
                    point, DATA(point), PREV(point), point, NEXT(point));
        } else {
            fprintf(file, "\"%d\" [fillcolor=\"#FFFF00\", label=\"{%d[FREE]|{%d|%u|%d}}\"]\n",
                    point, DATA(point), PREV(point), point, NEXT(point));
        }
    }

    //fprintf (file, "\"-1\" [ style = invis ];\n");

    index_t link = HEAD;

    for (index_t point = 1; point <= LENGTH; point++) {

        if (NEXT(link) > 0) {
            fprintf(file, "\"%d\"->\"%d\";\n", link, NEXT(link));
        }

        if (PREV(link) > 0) {
            fprintf(file, "\"%d\"->\"%d\";\n", link, PREV(link));
        }

        link = NEXT(link);
    }


    for (index_t point = 1; point <= CAPACITY; point++) {
        if (DATA(point) != POISON) {

            if (NEXT(point) == 0) {
                fprintf(file, "\"%d\"->\"%d\";\n", point, -3);

            }

            if (PREV(point) == 0) {
                fprintf(file, "\"%d\"->\"%d\";\n", -2, point);
            }

        }
    }

	fprintf(file, "}");

	fclose(file);

    system("dot -Tjpg PhysicalDump.txt > PhysicalDump.jpg");

    return true;
};

bool ListGraphLogical  (List* thisList) {

    FILE* file = fopen ("LogicalDump.txt", "wt");

    if (file == NULL) {
        return false;
    }

    fprintf (file, "digraph MyGraph {\n");
	fprintf (file, "node [shape=\"record\", style=\"filled\", color=\"#008000\", fillcolor=\"#C0FFC0\"];\n");

    fprintf (file, "\"%d\" [color=\"#000080\", fillcolor=\"#FFA500\", label=\"{HEAD}\"];\n", -2);
    fprintf (file, "\"%d\" [color=\"#000080\", fillcolor=\"#FFA500\", label=\"{TAIL}\"];\n", -1);

    index_t link = HEAD;

    for (index_t point = 1; point <= LENGTH; point++) {
        fprintf(file, "\"%d\" [fillcolor=\"#AFEEEE\", label=\"{%d|{%d|%u|%d}}\"]\n",
				    point, DATA(link), PREV(link), link, NEXT(link));
        link = NEXT(link);
    }

    fprintf (file, "\"%d\"->\"%d\";\n", -2, 1);

    for (index_t point = 1; point < LENGTH; point++) {
            fprintf(file, "\"%d\"->\"%d\";\n", point, point++);
            fprintf(file, "\"%d\"->\"%d\";\n", point, point--);
    }

    fprintf (file, "\"%d\"->\"%d\";\n", LENGTH, -1);

	fprintf (file, "}");

	fclose (file);

    system ("dot -Tjpg LogicalDump.txt > LogicalDump.jpg");

    return true;

};


bool ListOK (List* thisList) {

    if (thisList == NULL) {
        return false;

    }

    for (index_t point = 1; point <= LENGTH; point++) {
        if (thisList->next[point] == thisList->prev[point]) {
            return false;

        }
    }

    if (TAIL < 0 || TAIL > CAPACITY) {
        return false;

    }

    if (HEAD < 0 || HEAD > CAPACITY) {
        return false;

    }

    return true;
};

void ConsoleDump(List* thisList) {

    printf("= = = DUMP OF LIST = = =\n");

    printf("List* thisList [%ld] (%d) {\n", thisList, ListOK(thisList));
    printf("    thisList->length   = %d;\n", LENGTH);
    printf("    thisList->capacity = %d;\n\n", CAPACITY);

    printf("    thisList->head = %d;\n", HEAD);
    printf("    thisList->tail = %d;\n", TAIL);
    printf("    thisList->free = %d;\n\n", FREE);

    printf("    thisList->data [%ld] {\n", thisList->data);
    for (index_t point = 0; point < CAPACITY; point++) {
        printf("        [%d] %d ", point, DATA(point));
        if (DATA(point) == POISON) {
            printf("(POISON!)");
        }
        printf("\n");
    };
    printf("    }\n\n");

    printf("    thisList->prev [%ld] {\n", thisList->prev);
    for (index_t point = 0; point < CAPACITY; point++) {
        printf("        [%d] %d\n", point, PREV(point));
    };
    printf("    }\n\n");

    printf("    thisList->next [%ld] {\n", thisList->next);
    for (index_t point = 0; point < CAPACITY; point++) {
        printf("        [%d] %d\n", point, NEXT(point));
    };
    printf("    }\n\n");

    printf("- - - END OF DUMP - - -\n\n");
};

void ConsoleData(List* thisList) {

    printf("~ ~ ~ DATA OF LIST ~ ~ ~\n");

    index_t link = HEAD;

    for(index_t point = 1; point <= LENGTH; point++) {
        printf("[%d] %d\n", point, DATA(link));
        link = NEXT(link);
    }

    printf("* * * END OF DATA * * *\n\n");
};
