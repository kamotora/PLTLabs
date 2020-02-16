//
// Created by artem on 30.10.2019.
//

#include "Tree.h"

Tree *Tree::cur;

Tree::Tree() {
    node = new Node(TNodeEmpty);
    up = NULL;
    left = NULL;
    right = NULL;

    cur = this;

}

Tree::Tree(Tree *_left, Tree *_right, Tree *_up, Node *_node) {
    node = new Node();
    up = _up;
    left = _left;
    right = _right;
    memcpy(node, _node, sizeof(Node));
}

// создать левого потомка от текущей вершины this
void Tree::setLeft(Node *data) {
    Tree *a = new Tree(NULL, NULL, this, data);
    left = a;
}

// создать правого потомка от текущей вершины this
void Tree::setRight(Node *data) {
    Tree *a = new Tree(NULL, NULL, this, data);
    right = a;
}

Tree *Tree::findUp(Tree *from, TypeLex id) {
    Tree *current = from;
    while (current != NULL && strcmp(id, current->node->id) != 0) {
        current = current->up;
    }
    return current;
}

Tree *Tree::findUp(int typeNode) {
    Tree *current = cur;
    while (current != NULL && typeNode != current->node->typeNode != 0) {
        current = current->up;
    }
    return current;
}

Tree *Tree::findUp(TypeLex id) {
    return findUp(this, id);
}

Tree *Tree::findRightLeft(Tree *from, TypeLex id) {
    Tree *current = from->right;
    while (current != NULL && strcmp(id, current->node->id) != 0) {
        current = current->left;
    }
    return current;
}

Tree *Tree::findRightLeft(TypeLex id) {
    return findUp(this, id);
}

Tree *Tree::findUpOneLevel(Tree *from, char *id) {
    Tree *current = from;
    while (current != NULL && current->up != NULL && current->up->right != current) {
        if (strcmp(id, current->node->id) == 0) {
            return current;
        }
        current = current->up;
    }
    return NULL;
}


// отладочная программа печати дерева для интерпретатора
void Tree::printTree() {

    if (node->typeNode != TNodeEmpty) {

        printf("Вершина с данными %s ", node->id);

        if (node->typeNode == TNodeVar)
            printf(" переменная типа");
        if (node->typeNode == TNodeFunction)
            printf(" функция возвр.тип ");
        printf(" %s", TDataToName(node->typeData).c_str());

    } else
        printf("Пустая вершина %s ", node->id);
    printf("\n");

    if (left != NULL) {
        printf("слева от %s: ", node->id);
        left->printTree();
    }
    if (right != NULL) {
        printf("справа: от %s: ", node->id);
        right->printTree();
    }

}

void Tree::setCur(Tree *a) {
    cur = a;
}

Tree *Tree::getCur() {
    return cur;
}

void Tree::semSetTypeNode(Tree *addr, int typeNode) {
    addr->node->typeNode = typeNode;
}

void Tree::semSetTypeData(Tree *addr, int typeData) {
    addr->node->typeData = typeData;
}

// проверка идентификатора на повторное описание внутри блока
int Tree::dupControl(Tree *addr, TypeLex id) {
    if (findUpOneLevel(addr, id) == NULL)
        return 0;
    return 1;
}

// найти в таблице переменную с именем а
Tree *Tree::semGetVar(TypeLex a, Scanner *sc) {
    Tree *v = findUp(cur, a);
    if (v == NULL) {
        //printTree();
        sc->printError("отсутствует описание идентификатора", a, false);
    } else if (v->node->typeNode == TNodeFunction)
        sc->printError("неверное использование вызова функции", a, false);
    return v;
}

// найти в таблице функцию с именем а (сем 2)
Tree *Tree::semGetFunc(TypeLex a, Scanner *sc) {
    Tree *v = findUp(cur, a);
    if (v == NULL)
        sc->printError("отсутствует описание идентификатора ф-ии", a, false);
    else if (v->node->typeNode == TNodeVar)
        sc->printError("попытка использовать переменную вместо функции", a, false);
    return v;
}

// занесение идентификатора в таблицу
Tree *Tree::semAddNode(TypeLex id, int typeNode, int typeData, Scanner *sc) {
    if (dupControl(cur, id))
        sc->printError("повторное описание идентификатора", id, false);
    Tree *v;
    Node *pNode = new Node(typeNode, id, typeData);
    cur->setLeft(pNode);
    cur = cur->left;
    if (typeNode == TNodeFunction) {
        // точка возврата после выхода из функции
        v = cur;
        Node emptyNode(TNodeEmpty);
        strcpy(emptyNode.id, "###");
        cur->setRight(&emptyNode);
        cur = cur->right;
        return v;
    }
    return cur;
}

Tree *Tree::semAddBlock() {
    Tree *v;
    Node emptyNode1(TNodeEmpty), emptyNode2(TNodeEmpty);
    strcpy(emptyNode1.id, "###");
    strcpy(emptyNode2.id, "###");
    cur->setLeft(&emptyNode1);
    //TODO хз
    v = cur;
    cur = cur->left;
    cur->setRight(&emptyNode2);
    cur = cur->right;
    return v;
}


Node *Tree::getNode() const {
    return node;
}

Tree *Tree::delBlock(bool needDeleteFunctions) {
    Tree *res = nullptr;
    /*
    if(this->node->typeNode == TNodeFunction){
        if(needDeleteFunctions){
            res = this->up;
            res->left->delTree();
            res->left = nullptr;
            return res;
        } else
            return this;
    }
     */
    res = this;
    //(res->left == this) ? res->left = nullptr : res->right = nullptr;
    this->left->delTree();
    res->left = nullptr;
    return res;
}

void Tree::delTree() {
    if (left != NULL)
        left->delTree();
    if (right != NULL)
        right->delTree();
    delete this;
}


