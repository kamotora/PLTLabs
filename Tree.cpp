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


// отладочная программа печати дерева
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

    if (right != NULL) {
        printf("справа: от %s: ", node->id);
        right->printTree();
    }

    if (left != NULL) {
        printf("слева от %s: ", node->id);
        left->printTree();
    }


}

void Tree::setCur(Tree *a) {
    Tree::cur = a;
}

Tree *Tree::getCur() {
    return Tree::cur;
}