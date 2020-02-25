//
// Created by artem on 30.10.2019.
//

#include "Tree.h"

Tree *Tree::cur;
long long create = 0, del = 0;
Tree::Tree() {
    node = new Node(TNodeEmpty);
    up = NULL;
    left = NULL;
    right = NULL;
}

Tree::Tree(Tree *_left, Tree *_right, Tree *_up, Node *_node) {
    node = new Node();
    up = _up;
    left = _left;
    right = _right;
    node = _node;
}

Tree::~Tree() {
    delete node;
    node = nullptr;
}

Tree *Tree::getUp() const {
    return up;
}

Tree *Tree::getLeft() const {
    return left;
}

Tree *Tree::getRight() const {
    return right;
}

// создать левого потомка от текущей вершины this
void Tree::setLeft(Node *data) {
    if (left != nullptr)
        delete left;
    left = new Tree(nullptr, nullptr, this, data);
}

// создать правого потомка от текущей вершины this
void Tree::setRight(Node *data) {
    if (right != nullptr)
        delete right;
    right = new Tree(nullptr, nullptr, this, data);
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
    Tree::cur = a;
}

Tree *Tree::getCur() {
    return Tree::cur;
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
    if (cur == nullptr)
        cur = this;
    cur->setLeft(new Node(typeNode, id, typeData));
    cur = cur->left;
    if (typeNode == TNodeFunction) {
        // точка возврата после выхода из функции
        cur->setRight(new Node(TNodeEmpty));
        //cur = cur->right;
        return cur;
    }
    return cur;
}

//Возвращает указатель на блок
Tree *Tree::semAddBlock() {
    if (cur == nullptr)
        cur = this;
    printf("Добавили пустую вершину\n");
    Tree *v;
    cur->setLeft(new Node(TNodeEmpty));
    cur = cur->left;
    v = cur;
    printf("Добавили пустую вершину\n");
    cur->setRight(new Node(TNodeEmpty));
    cur = cur->right;
    return v;
}


Node *Tree::getNode() const {
    return node;
}

void Tree::delBlock(Tree *tree) {
    //Удаляем указатель на данное поддерево
    (tree->up->left == tree) ? tree->up->left = nullptr : tree->up->right = nullptr;
    setCur(tree->up);
    //Удаляем само поддерево
    FreeTree(tree);
}

void Tree::FreeTree(Tree *tree) {
    if (tree == nullptr)
        return;
    if (tree->left) FreeTree(tree->left);
    if (tree->right) FreeTree(tree->right);
    (tree->up->left == tree) ? tree->up->left = nullptr : tree->up->right = nullptr;
    del += sizeof(tree);
    printf("Удалили %s\n", tree->getNode()->id);
    delete tree;
    tree = nullptr;
}

void Tree::delBlockv2() {
    while (cur->node->typeNode != TNodeEmpty) {
        if (cur->left) delete cur->left;
        if (cur->right) delete cur->right;
        cur = cur->up;
    }
    if (cur->left) delete cur->left;
    if (cur->right) delete cur->right;
    cur = cur->up;
    if (cur->left) delete cur->left;
    if (cur->right) delete cur->right;
    cur = cur->up;
    cur->left = cur->right = nullptr;
}



