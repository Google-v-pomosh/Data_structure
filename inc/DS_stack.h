#pragma once
#include <iostream>
#include <stack>
using namespace std;

// Стек

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();
    Stack<T> &operator=(const Stack<T> &other); // присваивает значения адаптеру контейнера
    T top();
    bool empty();               // проверяет пуст ли стек
    int size() { return Size; } // возвращает количество элементов
    void push(T data);          // вставляет элемент вверх
    void emplace(T data);       // создает элемент на месте вверху
    void pop();                 // удаляет верхний элемент
    void swap();                // переворачивает стак
    void PrintStack();          // выводит содержимое стака
private:
    template <typename U>
    class NodeStack
    {
    public:
        NodeStack *pNext;
        U Data;
        NodeStack(U data = U(), NodeStack *pNext = nullptr)
        {
            this->Data = data;
            this->pNext = pNext;
        }
    };
    int Size;
    NodeStack<T> *head;
};

// Стек

template <typename T>
Stack<T>::Stack()
{
    Size = 0;
    head = nullptr;
    cout << "Constructor" << endl;
}

template <typename T>
Stack<T>::~Stack()
{
    while (!empty())
    {
        pop();
    }
    cout << "Destructor" << endl;
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    while (!empty())
    {
        pop();
    }
    NodeStack<T> *current = other.head;
    while (current != nullptr)
    {
        push(current->Data);
        current = current->pNext;
    }
    return *this;
}

template <typename T>
bool Stack<T>::empty()
{
    if (Size != 0)
    {
        return false;
    }
}

template <typename T>
T Stack<T>::top()
{
    if (empty())
    {
        cout << "EROR" << endl;
    };
    cout << head->Data << endl;
}

template <typename T>
void Stack<T>::push(T data)
{
    if (head == nullptr)
    {
        head = new NodeStack<T>(data);
    }
    else
    {
        NodeStack<T> *current = this->head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new NodeStack<T>(data);
    }
    Size++;
}

template <typename T>
void Stack<T>::pop()
{
    NodeStack<T> *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

template <typename T>
void Stack<T>::swap()
{
    if (Size <= 1)
    {
        return;
    }
    else
    {
        NodeStack<T> *previous = nullptr;
        NodeStack<T> *current = head;
        while (current != nullptr)
        {
            NodeStack<T> *next = current->pNext;
            current->pNext = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }
}

template <typename T>
void Stack<T>::PrintStack()
{
    if (empty())
    {
        cout << "Stack is empty" << endl;
    }
    else
    {
        NodeStack<T> *current = head;
        while (current != nullptr)
        {
            cout << current->Data << " ";
            current = current->pNext;
        }
        cout << endl;
    }
}

template <typename T>
void Stack<T>::emplace(T data)
{
    NodeStack<T> *newNode = new NodeStack<T>(data, head);
    head = newNode;
    Size++;
}