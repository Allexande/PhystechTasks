//Version 0.1

List* ListConstruct (size_t capacity) {

    List* newList = (List*) calloc (sizeof(List), 1);
    assert (newList);

    newList->data = (elem_t*) calloc (sizeof(elem_t), capacity);
    assert (newList->data);
    newList->next = (index_t*) calloc (sizeof(index_t), capacity);
    assert (newList->next);
    newList->prev = (index_t*) calloc (sizeof(index_t), capacity);
    assert (newList->prev);

    newList->head = 1;
    newList->tail = 1;
    newList->free = 1;

    newList->length   = 0;
    newList->capacity = capacity;

    for (size_t point = 1; point <= capacity; point++) {
		newList->prev[point] = -1;
		newList->next[point] = point + 1;
    }

    ASSERT_OK(newList)

    return newList;
};

index_t GetIndexFromOrder (List* thisList, index_t number) {

    ASSERT_OK(thisList)

	index_t indexToFind = thisList->head;
	if (number > thisList->length) {
        return -1;
    }

	for (index_t point = 1; point < number; point++) {
        if (point > thisList->length) {
            return -1;
        };
		indexToFind = thisList->next[indexToFind];
	}

	return indexToFind;
};

bool TryToRealloc (List* thisList) {

    if (thisList->length >= thisList->capacity) {

        thisList->data = (elem_t*) realloc (thisList->data, sizeof(elem_t)  * thisList->capacity * REALLOC_UP);
        assert(thisList->data);
        thisList->next = (index_t*) realloc (thisList->next, sizeof(index_t) * thisList->capacity * REALLOC_UP);
        assert(thisList->next);
        thisList->prev = (index_t*) realloc (thisList->prev, sizeof(index_t) * thisList->capacity * REALLOC_UP);
        assert(thisList->prev);

        thisList->free = thisList->capacity;

		for (index_t point = thisList->capacity; point <= thisList->capacity * REALLOC_UP; point++) {
			thisList->next[point] = point + 1;
			thisList->prev[point] = -1;
		}

		thisList->capacity *= REALLOC_UP;

		thisList->next[thisList->capacity] = 0;

        return true;
    }

    return false;
};

index_t ListInsertAtIndex (List* thisList, elem_t newElem, index_t index) {

    ASSERT_OK(thisList)

	thisList->length++;

	TryToRealloc(thisList);

	if (index == 0) {
		return ListInsertBegin(thisList, newElem);
	}

	index_t nextIndex = GetIndexFromOrder(thisList, index);

	if (nextIndex == thisList->tail) {
		return ListInsertEnd(thisList, newElem);
	}

	index_t insertedIndex = thisList->free;
    thisList->free = thisList->next[thisList->free];

	thisList->prev[insertedIndex] = nextIndex;
	thisList->next[insertedIndex] = thisList->next[nextIndex];

	thisList->prev[thisList->next[insertedIndex]] = insertedIndex;
	thisList->next[nextIndex] = insertedIndex;

	thisList->data[insertedIndex] = newElem;
	return insertedIndex;
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

	thisList->length++;

	TryToRealloc(thisList);

	index_t insertedIndex = thisList->free;
    thisList->free = thisList->next[thisList->free];

	thisList->prev[thisList->head] = insertedIndex;

	thisList->data[insertedIndex] = newElem;
	thisList->next[insertedIndex] = thisList->head;
	thisList->prev[insertedIndex] = 0;

	thisList->head = insertedIndex;

	return insertedIndex;
};

index_t ListInsertEnd (List* thisList, elem_t newElem) {
    ASSERT_OK(thisList)

	thisList->length++;

	TryToRealloc(thisList);

	index_t insertedIndex = thisList->free;
    thisList->free = thisList->next[thisList->free];

	thisList->next[thisList->tail] = insertedIndex;

	thisList->data[insertedIndex] = newElem;
	thisList->next[insertedIndex] = thisList->tail;
	thisList->prev[insertedIndex] = 0;

	thisList->tail = insertedIndex;

	return insertedIndex;
};

bool ListEraseAtIndex (List* thisList, index_t index) {

    ASSERT_OK(thisList)

    index = GetIndexFromOrder (thisList, index);

    if (index < 0) {
        return false;
    }

    thisList->length--;

    thisList->prev[thisList->next[index]] = thisList->prev[index];
    thisList->next[thisList->prev[index]] = thisList->next[index];

    thisList->next[index] = thisList->free;
    thisList->prev[index] = -1;
    thisList->free = index;

	return true;
};

bool ListEraseFromBegin (List* thisList) {
    index_t elem = thisList->next[thisList->head];
	bool result = ListEraseAtIndex(thisList, 1);
	thisList->head = elem;
    return result;
};

bool ListEraseFromEnd (List* thisList) {
    index_t elem = thisList->prev[thisList->tail];
    bool result = ListEraseAtIndex(thisList, thisList->length);
    thisList->tail = elem;
    return result;
};

bool HTMLList (List* thisList) {
    FILE* file = fopen ("list.html", "w");

    if (file == NULL) {
        return false;
    }

    fprintf (file, "<html> <head> <style> .container { overflow:hidden; } .info { white-space:nowrap; } .info div { width:30%; display:inline-block; border:1px solid black; } .adress { background:gray; margin:5px; } .node { width:200px; border:1px solid black; padding-bottom: 5px; padding-left: 5px; padding-right: 5px; padding-top: 5px; background:red; margin:5px; } .nodeadress { background:yellow; } .next { background:brown; } .prev { background:purple; } </style> </head> <body>");

    for (index_t point = 0; point < thisList->capacity; point++) {
        fprintf (file, "<div class='node'> <center class='adress's>%d</center> <div class='container'> <div class='info'> <div class='nodeAdress'>%d</div> <div class='next'>%d</div> <div class='prev'>%d</div> </div> </div> </div>", GetIndexFromOrder(thisList, point), thisList->data[point], thisList->next[point], thisList->prev[point]);
    }

    fprintf (file, "</body></html>");
	fclose (file);

    return true;
};

bool ListOK (List* thisList) {

    if (thisList->length > thisList->length) {
        return false;
    }

    for (index_t point = 1; point <= thisList->length; point++) {
        if (thisList->next[point] == thisList->prev[point]) {
            return false;
        }
    }

    if (thisList->tail < 0 || thisList->tail > thisList->capacity) {
        return false;
    }

    if (thisList->head < 0 || thisList->head > thisList->capacity) {
        return false;
    }

    return true;
};

void ConsoleDump(List* thisList) {

    printf("= = = DUMP OF LIST = = =\n");

    printf("List* thisList [%ld] (%d) {\n", thisList, ListOK(thisList));
    printf("    thisList->length   = %d;\n", thisList->length);
    printf("    thisList->capacity = %d;\n\n", thisList->capacity);

    printf("    thisList->head = %d;\n", thisList->head);
    printf("    thisList->tail = %d;\n", thisList->tail);
    printf("    thisList->free = %d;\n\n", thisList->free);

    printf("    thisList->data [%ld] {\n", thisList->data);
    for (index_t point = 0; point < thisList->capacity; point++) {
        printf("        [%d] %d\n", point, thisList->data[point]);
    };
    printf("    }\n\n");

    printf("    thisList->prev [%ld] {\n", thisList->prev);
    for (index_t point = 0; point < thisList->capacity; point++) {
        printf("        [%d] %d\n", point, thisList->prev[point]);
    };
    printf("    }\n\n");

    printf("    thisList->next [%ld] {\n", thisList->next);
    for (index_t point = 0; point < thisList->capacity; point++) {
        printf("        [%d] %d\n", point, thisList->next[point]);
    };
    printf("    }\n\n");

    printf("- - - END OF DUMP - - -\n");
};

void ConsoleData(List* thisList) {

    printf("~ ~ ~ DATA OF LIST ~ ~ ~\n");

    index_t link = thisList->head;

    for(index_t point = 1; point <= thisList->length; point++) {
        printf("[%d] %d\n", point, thisList->data[link]);
        link = thisList->next[link];
    }

    printf("* * * END OF DATA * * *\n");
};
