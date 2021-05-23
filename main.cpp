#include <iostream>
#include "defs.h"
#include "Scanner.h"
#include "LL1.h"
//#include "Scanner.cpp"
//#include "Tree.cpp"
//#include "LL1.cpp"
//#include "defs.cpp"

using namespace std;

int main(int argc, char *argv[]) {
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
//    ll1->outTree();
//    ll1->outOperands();
    cout << "До оптимизации" << endl;
    ll1->outTriads();
    ll1->optimize();
    cout << "После оптимизации" << endl;
    ll1->outTriads();
    int type;
    TypeLex lex;
    type = sc->scanner(lex);

    if (type == TEnd)
        cout << "Синтаксических ошибок не обнаружено. \n";
    else
        sc->printError("Лишний текст в конце программы.");
    return 0;

//    int i = 0;
//    cond:
//        if(i < 10)
//            goto body;
//        goto end;
//    step:
//        i++;
//        goto cond;
//    body:
//    {
//        cout << "kek";
//    }
//    goto step;
//    end:;
//
//    body2:
//    {
//        cout << "kek";
//    }
//    cond2:
//    if(i < 10)
//        goto body2;
//
//
//    cond3:
//    if(i < 10)
//        goto body3;
//    goto end3;
//    body3:
//    {
//        cout << "kek";
//    }
//    goto cond3;
//    end3:;
}