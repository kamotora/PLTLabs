#include <iostream>
#include "defs.h"
#include "Scanner.h"
#include "Diagram.h"
//#include "Scanner.cpp"
//#include "Diagram.cpp"

using namespace std;
int main(int argc, char *argv[]) {
    Scanner * sc ;
    const char * fileName = "input.cpp";
    if (argc <= 1)
        // файл по умолчанию
        sc = new Scanner(fileName);
    else
        // заданный файл
        sc = new Scanner(argv[1]);
    /*
    do {
        type=sc->scanner(l);
        printf("%s - тип %d \n",l, type);
    } while(type!=TEnd);
    */
    Diagram *diagram = new Diagram(sc);
    diagram->prog();
    int type; TypeLex lex;
    type=sc->scanner(lex);
    if (type==TEnd)
        printf("Синтаксических ошибок не обнаружено. \n");
    else
        sc->printError("Лишний текст в конце программы.");
    return 0;
}