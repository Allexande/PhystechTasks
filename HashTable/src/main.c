#include <stdio.h>

#include "HashFuncs.h"
#include "HashTable.h"
#include "HashTest.h"

#include "Unit-Test.h"

//TODO заменить проверку на нулевые указатели во всей программе

//TODO удалять все структуры в конце

//TODO все переводимые слова к нижнему регистру

#define ENG_WORDS_LIST_FILE "C://Cprojects//dictionary//WordsList.txt"

char* concat(char *s1, char *s2) {

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1);

    if (result == NULL) {
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);

    return result;
}

int main() {
    /*
    struct List* testList = CreatList ();

    AppendNode (testList, CreatePair ("milk", "tasty"));
    AppendNode (testList, CreatePair ("cook", "liketoDOit"));
    AppendNode (testList, CreatePair ("who", "Iam"));

    ConsoleBumpOfLinkedList (testList);
    */
    //return CreateReport (ENG_WORDS_LIST_FILE);





    //struct HashTable* table = BuildHashTable ("C:\\Cprojects\\dictionary\\dic.txt", 199, GetDJB2Hash);

    //ConsoleBumpOfHashTable (table);


    //UNCOMMENT THIS!!!
    TranslateWebPage ("C:\\Users\\AlexanderT\\CLionProjects\\EngRusTrans\\data\\test.html", "C:\\Users\\AlexanderT\\CLionProjects\\EngRusTrans\\data\\out.html");

    //GeneralTest ();

    //WriteTextInFile ("C:\\Cprojects\\dictionary\\test.txt", FindByKey(table, "hey am so happy to see you there! how are you?"));

    //char* msg = FindByKey(table, "\"sasha is going to explare this question\"");
    //system(concat("C:\\Users\\AlexanderT\\Pictures\\balcon\\balcon.exe -id 1049 -enc utf8 -t ", msg));

    //WriteTextInFile ("C:\\Cprojects\\dictionary\\test.txt", PhoneticTranslation ("hello, my name is sasha. this is translator of english language"));

    /*
    for (int i = 0; i < 512; i++) {
        printf ("[%d] %c\n", i, i);
    }
*/
    return 0;
}