//Version 1.5.1

#include "list.h"

#define POISON 30234

#define WARNINGS

//Defines for working with list

#define NEXT(pointer) thisList->next[pointer]
#define PREV(pointer) thisList->prev[pointer]
#define DATA(pointer) thisList->data[pointer]

#define HEAD thisList->head
#define TAIL thisList->tail
#define FREE thisList->free

#define LENGTH   thisList->length
#define CAPACITY thisList->capacity

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

    DATA(0) = POISON;

    for (size_t point = 1; point <= capacity; point++) {

        DATA(point) = POISON;
		PREV(point) = -1;
		NEXT(point) = point + 1;

    }

    NEXT(capacity) = -1;

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

	index_t indexToFind = HEAD;
	if (number > LENGTH) {
        return -1;

    }

	for (index_t point = 1; point < number; point++) {

        if (point > LENGTH) {
            return -1;

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
			thisList->prev[point] = -1;
		}

		CAPACITY *= REALLOC_UP;

        NEXT(CAPACITY) = -1;

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

	LENGTH++;

	TryToRealloc(thisList);

	index_t insertedIndex = FREE;
    FREE = NEXT(FREE);

	PREV(HEAD) = insertedIndex;

	DATA(insertedIndex) = newElem;
	NEXT(insertedIndex) = HEAD;
	PREV(insertedIndex) = -1;

	HEAD = insertedIndex;

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
	NEXT(insertedIndex) = TAIL;
	PREV(insertedIndex) = -1;

	TAIL = insertedIndex;

	return insertedIndex;
};

index_t ListInsertAtPlace (List* thisList, elem_t newElem, index_t place) {

    LENGTH++;

	TryToRealloc (thisList);

    if (place == TAIL) {
		return ListInsertEnd(thisList, newElem);

	}

    //??
	if (place == 0) {
        return ListInsertBegin(thisList, newElem);

	}

	if (place > CAPACITY || DATA(place) == POISON) {
        return -1;

	}

	index_t insertedIndex = FREE;
    FREE = NEXT(FREE);

	PREV(insertedIndex) = place;
	NEXT(insertedIndex) = NEXT(place);

	PREV(NEXT(insertedIndex)) = insertedIndex;
	NEXT(place) = insertedIndex;

	DATA(insertedIndex) = newElem;

	return place;
};

index_t ListEraseAtIndex (List* thisList, index_t index) {

    ASSERT_OK(thisList)

    if (index > LENGTH) {
        return -1;

    }

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

    PREV(NEXT(place)) = PREV(place);
    NEXT(PREV(place)) = NEXT(place);

    DATA(place) = POISON;
    NEXT(place) = FREE;
    PREV(place) = -1;

    FREE = place;

    return place;
};


elem_t ListGetByOrder (List* thisList, index_t order) {

    ASSERT_OK(thisList)

    if (order > LENGTH) {
        return POISON;

    }

    index_t link = HEAD;

    for (index_t point = 1; point <= order; point++) {
        link = NEXT(link);
    }

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
            fprintf (file, DeleteExcessSpaces ("<div class=\"node\">              \
                                <center class=\"adress\">%d</center>              \
                                    <div class=\"container\">                     \
                                        <div class=\"info\">                      \
                                            <div class=\"data field\">%d</div>    \
                                            <div class=\"next field\">%d</div>    \
                                            <div class=\"prev field\">%d</div>    \
                                        </div>                                    \
                                    </div>                                        \
                                </div>"),
            GetIndexFromOrder(thisList, point),
            DATA(point),
            NEXT(point),
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
            GetIndexFromOrder(thisList, point),
            DATA(point),
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
        link,
        DATA(link),
        NEXT(link),
        PREV(link));

        link = NEXT(link);

    }

    //Adding ending of second column and beginning (title) of third column
    fprintf (file, DeleteExcessSpaces ("<div class=\"node\" style=\"background:Orange\">              \
                        TAIL                                                                          \
                    </div>                                                                            \
                </td>                                                                                 \
                <td>                                                                                  \
                    <p>                                                                               \
                        This is dump of special list.                                                 \
                    </p>                                                                              \
                    <div class=\"node\">                                                              \
                        <center class=\"adress\">                                                     \
                            POSITION                                                                  \
                        </center>                                                                     \
                        <div class=\"container\">                                                     \
                            <div class=\"info\">                                                      \
                                <div class=\"data field\">                                            \
                                    DATA                                                              \
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
        POSITION - the locical position of node in array in memory                                    \
        <br>DATA - the value which the node keeps                                                     \
        <br>NEXT - the pointer on physical position of next node                                      \
        <br>PREV - the pointer on physical position of previous node                                  \
        <br><br>Free nodes have value which is equal to POISON (%d)                                   \
    </p>"), POISON);

    //Adding the end of JS command
    fprintf (file, "';");

	fclose (file);

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
        printf("        [%d] %d ", point, thisList->data[point]);
        if (thisList->data[point] == POISON) {
            printf("(POISON!)");
        }
        printf("\n");
    };
    printf("    }\n\n");

    printf("    thisList->prev [%ld] {\n", thisList->prev);
    for (index_t point = 0; point < CAPACITY; point++) {
        printf("        [%d] %d\n", point, thisList->prev[point]);
    };
    printf("    }\n\n");

    printf("    thisList->next [%ld] {\n", thisList->next);
    for (index_t point = 0; point < CAPACITY; point++) {
        printf("        [%d] %d\n", point, thisList->next[point]);
    };
    printf("    }\n\n");

    printf("- - - END OF DUMP - - -\n\n");
};

void ConsoleData(List* thisList) {

    printf("~ ~ ~ DATA OF LIST ~ ~ ~\n");

    index_t link = HEAD;

    for(index_t point = 1; point <= LENGTH; point++) {
        printf("[%d] %d\n", point, thisList->data[link]);
        link = thisList->next[link];
    }

    printf("* * * END OF DATA * * *\n\n");
};
