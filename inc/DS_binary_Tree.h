#pragma once
#include <iostream>
#include <stack>
using namespace std;

// Бинарное дерево

template <typename T>
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void insert(const T &data); // Реализация вставки узла в дерево
    bool search(const T &data); // Реализация поиска значения в дереве
    void remove(const T &data); // Реализация удаления значения из дерева
    void traverseInOrder();     // Реализация обхода дерева в порядке in-order
    void traversePreOrder();    // Реализация обхода дерева в порядке pre-order
    void traversePostOrder();   // Реализация обхода дерева в порядке post-order
    void clear();               // Реализация очистки дерева
private:
    template <typename U>
    class NodeBinaryTree
    {
    public:
        U data;
        NodeBinaryTree<U> *left;
        NodeBinaryTree<U> *right;
        NodeBinaryTree(U data = U(), NodeBinaryTree<U> *left = nullptr, NodeBinaryTree<U> *right = nullptr)
        {
            this->data = data;
            this->left = left;
            this->right = right;
        }
    };
    int height;
    NodeBinaryTree<T> *root;
};

// бинарное дерево

template <typename T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
    height = 0;
    cout << "Constructor" << endl;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    cout << "Destructor" << endl;
}

template <typename T>
void BinaryTree<T>::insert(const T &data)
{
    NodeBinaryTree<T> *NewNode = new NodeBinaryTree<T>(data); // создаем новый узел с переданным значением
    if (root == nullptr)
    {                   // проверяем на наличие элементов в дереве
        root = NewNode; // если элементов в дереве нет, то создаем корень дерева из 1ого узла
        height++;       // счетчик высоты дерева
        return;
    }
    NodeBinaryTree<T> *current = root;   // указатель на текущий узел, инициализируется указателем на корень дерева
    NodeBinaryTree<T> *parent = nullptr; // указатель на родительский узел текущего узла, используется для хранения родительского узла перед перемещением
    while (true)
    {                     // используется для поиска места вставки нового узла в бинарное дерево
        parent = current; // Запоминаем текущий узел как родительский узел
        if (data < current->data)
        {
            {                           // Если достигнут конец пути, вставляем новый узел, как левого потомка родительского узла
                parent->left = NewNode; // устанавливает левого потомка родительского узла parent в новый узел newNode во время вставки нового узла в бинарное дерево.
                height++;               // счетчик высоты дерева
                return;
            }
        }
        else
        {                             // иначе
            current = current->right; // перемещает указатель на правого потомка текущего узла во время поиска места для вставки нового узла
            if (current == nullptr)
            {                            // Если достигнут конец пути, вставляем новый узел, как левого потомка родительского узла
                parent->right = NewNode; // устанавливает правого потомка родительского узла parent в новый узел newNode во время вставки нового узла в бинарное дерево
                height++;                // счетчик высоты дерева
                return;
            }
        }
    }
}

template <typename T>
bool BinaryTree<T>::search(const T &data)
{
    NodeBinaryTree<T> *current = root; // Устанавливаем текущий узел как корень дерева
    while (current != nullptr)
    { // Пока текущий узел не станет nullptr (не достигнут конец пути)
        if (data == current->data)
        { // Если значение совпадает с данными текущего узла, значит, значение найдено в дереве
            return true;
        }
        else if (data < current->data)
        { // Если значение меньше значения текущего узла, двигаемся влево по дереву
            current = current->left;
        }
        else
        {
            current = current->right; // Если значение больше значения текущего узла, двигаемся вправо по дереву
        }
    }
    return false; // Если значение не найдено в дереве, возвращаем false
}