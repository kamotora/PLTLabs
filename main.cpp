#include <iostream>
#include "defs.h"
#include "Scanner.h"
#include "LL1.h"
// #include <windows.h>

//#include "Scanner.cpp"
//#include "Tree.cpp"
//#include "LL1.cpp"
//#include "defs.cpp"

using namespace std;

int main(int argc, char *argv[]) {
//     SetConsoleOutputCP(CP_UTF8);
    Scanner *sc;
    const char *fileName = "input.cpp";
    if (argc <= 1)
        // файл по умолчанию
        sc = new Scanner(fileName);
    else
        // заданный файл
        sc = new Scanner(argv[1]);
    LL1 *ll1 = new LL1(sc);
    ll1->LL_1();
    int type;
    TypeLex lex;
    type = sc->scanner(lex);

    if (type == TEnd)
        printf("Синтаксических ошибок не обнаружено. \n");
    else
        sc->printError("Лишний текст в конце программы.");
    return 0;
}
