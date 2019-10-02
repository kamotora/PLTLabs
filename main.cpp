#include <iostream>
#include "defs.h"
#include "Scanner.h"

using namespace std;
int main(int argc, char *argv[]) {
    for(int i = 0; i < argc; i++)
        cout << argv[i] << endl;
    TScanner * sc ;
    int type; TypeLex l;
    const char * fileName = "input.cpp";
    if (argc <= 1)
        // файл по умолчанию
        sc = new TScanner(fileName);
    else
        // заданный файл
        sc = new TScanner(argv[1]);
    do {
        type=sc->scanner(l);
        printf("%s - тип %d \n",l, type);
    } while(type!=TEnd);
    return 0;
}