#pragma once
#include <iostream>
#include <stack>
using namespace std;

// Двусвязный список

template <typename T>
class ListTest
{
public:
    ListTest();
    ~ListTest();
    void push_front(T data);        // отвечает за добавление элемента в начало списка
    void push_back(T data);         // отвечает за добавление элемента в конец списка
    void pop_front();               // удаляет самый первый элемент списка
    void pop_back();                // удаляет элемент из конца списка
    void insert(T data, int index); // вставляет какой либо элемент по указанному индексу (параметрами передается сам элемент и индекс по которому эти данные должны вставлены)
    void clear();                   // освобождение динамической памяти из всего односвязкого списка
    void removeAt(int index);       // удаляет элемент из списка по указанному индексу
    T &operator[](const int index);
    int GetSize() { return Size; }

private:
    template <typename U>
    class NodeTest
    {
    public:
        U data;
        NodeTest<U> *pNext;
        NodeTest<U> *pPrev;
        NodeTest(U data = U(), NodeTest *pNext = nullptr, NodeTest *pPrev = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };
    int Size;
    NodeTest<T> *head;
    NodeTest<T> *tail;
};

// Двусвязный список

template <typename T>
ListTest<T>::ListTest()
{
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template <typename T>
ListTest<T>::~ListTest()
{
    clear();
};

template <typename T>
void ListTest<T>::push_back(T data)
{
    NodeTest<T> *current = new NodeTest<T>(data);
    if (tail == nullptr)
    {
        head = current;
        tail = current;
    }
    else
    {
        current->pNext = nullptr;
        current->pPrev = tail;
        tail->pNext = current;
        tail = current;
    }
    Size++;
}

template <typename T>
void ListTest<T>::pop_front()
{
    NodeTest<T> *temp = head;
    head = head->pNext;
    if (head)
    {
        head->pPrev = nullptr;
    }
    else
    {
        tail = nullptr;
    }
    delete temp;
    Size--;
}

template <typename T>
void ListTest<T>::pop_back()
{
    NodeTest<T> *temp = tail;
    tail = tail->pPrev;
    if (tail)
    {
        tail->pNext = nullptr;
    }
    else
    {
        head = nullptr;
    }
    delete temp;
    Size--;
}

template <typename T>
void ListTest<T>::insert(T data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else if (index == Size)
    {
        push_back(data);
    }
    else if (index <= (Size / 2))
    {
        NodeTest<T> *current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->pNext;
        }
        NodeTest<T> *previous = new NodeTest<T>(data, current->pNext, current);
        current->pNext->pPrev = previous;
        current->pNext = previous;
        Size++;
    }
    else
    {
        NodeTest<T> *current = tail;
        for (int i = Size; i < index + 1; i--)
        {
            current = current->pPrev;
        }
        NodeTest<T> *previous = new NodeTest<T>(data, current->pPrev, current);
        current->pPrev->pNext = previous;
        current->pPrev = previous;
        Size++;
    }
}

template <typename T>
void ListTest<T>::clear()
{
    while (Size)
    {
        pop_front();
    }
}

template <typename T>
void ListTest<T>::removeAt(int index)
{
    if (index == 0)
    { // удаляем первый элемент
        pop_front();
    }
    else if (index == (Size - 1))
    { // удаляем последний элемент
        pop_back();
    }
    else
    { // удаляем элемент из середины
        if (index <= (Size / 2))
        {
            NodeTest<T> *previous = head;
            for (int i = 0; i < index - 1; i++)
            {
                previous = previous->pNext;
            }
            NodeTest<T> *toDelete = previous->pNext;
            NodeTest<T> *Next = toDelete->pNext;
            previous->pNext = Next;
            Next->pPrev = previous;
            delete toDelete;
        }
        else
        {
            NodeTest<T> *previous = tail;
            for (int i = Size - 1; i < index + 1; i--)
            {
                previous = previous->pPrev;
            }
            NodeTest<T> *toDelete = previous->pPrev;
            NodeTest<T> *Next = toDelete->pPrev;
            previous->pPrev = Next;
            Next->pNext = previous;
            delete toDelete;
        }
    }
    Size--;
};

template <typename T>
void ListTest<T>::push_front(T data)
{
    NodeTest<T> *current = new NodeTest<T>(data);
    if (head == nullptr)
    {
        head = current;
        tail = current;
    }
    else
    {
        current->pNext = head;
        head->pPrev = current;
        head = current;
    }
    Size++;
}

template <typename T>
T &ListTest<T>::operator[](const int index)
{
    int counter = 0;
    NodeTest<T> *current = this->head;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}