#pragma once
#include <iostream>
#include <stack>
using namespace std;

// Односвязный список

template <typename T>
class List
{
private:
    template <typename U>
    class Node
    {
    public:
        Node *pNext; // указатель на тип Node (adress) на следующий элемент односвязного списка
        U Data;      // данные
        bool visited;// значение, которое указывает была ли посещена нода
        Node(U data = U(), Node *pNext = nullptr, bool visited = false)
        { //*1, *2
            this->Data = data;
            this->pNext = pNext;
            this->visited = visited;
        }
    };
    int Size;      // переменная для определения размера списка
    Node<T> *head; // указатель на первый элемент в списке (указатель на тип Node)
public:
    List();
    ~List();
    void push_back(T data);             // отвечает за добавление элемента в конец списка
    void push_front(T data);            // отвечает за добавление элемента в начало списка
    void pop_front();                   // удаляет самый первый элемент списка
    void pop_back();                    // удаляет элемент из конца списка
    void insert(T data, int index);     // вставляет какой либо элемент по указанному индексу (параметрами передается сам элемент и индекс по которому эти данные должны вставлены)
    void insertCell(T data);            // вставляет элемент в отсортированный список по порядку
    void insertCelllimiter(T data);     // вставляет элемент в отсортированный список по порядку с использованием ограничителя
    void sort();                        // сортирует значения в спике в порядке возрастания
    void clear();                       // освобождение динамической памяти из всего односвязкого списка
    void revers();                      // переворачивает список
    void removeAt(int index);           // удаляет элемент из списка по указанному индексу
    int GetSize() { return Size; }      // возвращает кол-во элементов в списке
    void Iterate();                     // итерируется по всему списку, выводя в консоль все значения в односвязном списке
    bool Has_LoopMarking();             // позволяет определить есть ли в односвязном списке цикл
    bool CycleON(int index);            // создает цикл с началом в указанном индексе
    bool Has_LoopRetracing();           // производит повторную трассировку списка
    Node<T>* ReverseList(Node<T> *sentinel); // реверсирует список
    bool Has_LoopReversing();           // используем метод reverse чтобы определить наличие цикла
    bool hasCycle();                    // Алгоритм кролика и черепахи
    List<T> CopyList();                 // копирует односвязный список
    List<T> InsertionSort();
    T &findcell(T data);                // ищет в односвязком списке элемент
    T &findcellbefore(T data);          // ищет элемент перед искомым
    T &findcellbeforelimiter(T data);   // ищет элемент перед искомым, но с использованием ограничителя
    T &operator[](const int index);     // перегрузка оператора [] для итерирования по списку *4
};

// Односвязный список

template <typename T>
List<T>::List()
{
    Size = 0;       // хранение кол-ва элементов в односвязном списке
    head = nullptr; // указывает на самый первый элемент односвязного списка
    cout << "Constructor " <<  endl
         << endl;
}

template <typename T>
List<T>::~List()
{
    clear();
    cout << endl;
    cout << "Destructor" << endl;
}

template <typename T>
void List<T>::push_back(T data)
{
    if (head == nullptr)
    { // проверка первого элемента
        head = new Node<T>(data);
    }
    else
    {                                  //*3
        Node<T> *current = this->head; // Временная переменная (указатель на Node) изначально присваиваем значение заголовка
        while (current->pNext != nullptr)
        {                             // проверка на что указывает поле pNext текущего элемента (поиск последнего Node)
            current = current->pNext; // присваиваем указатель на следующий элемент
        }
        current->pNext = new Node<T>(data); // когда мы найдем элемент, адрес которого указывает на NULL, мы сможем создать новый элемент типа Node и адрес присвоить вместо NULL в конец списка
    }
    Size++;
}

template <typename T>
void List<T>::push_front(T data)
{
    head = new Node<T>(data, head); // указателю на первый элемент в списке (указатель на тип Node) присваивается новый элемент типа Node (передаем data, указатель на текущий head)
    Size++;
}

template <typename T>
void List<T>::pop_front()
{
    if (head == nullptr)
        return;
    Node<T> *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

template <typename T>
void List<T>::pop_back()
{
    removeAt(Size - 1); // находит последний элемент и удаляется его с помощью removeAt
}

template <typename T>
void List<T>::insert(T data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else
    {                                   // находим предыдущий элемент
        Node<T> *previous = this->head; // создаем временный указатель типа Node и присваиваем ему значение указателя на первый элемент в списке
        for (int i = 0; i < index - 1; i++)
        {                               // цикл, который находит элемент с индексом предшествующему идексу на место которого мы хотим поместить обьект
            previous = previous->pNext; // во временную переменную присваиваем указатель на следующую Node списка
        }
        Node<T> *newNode = new Node<T>(data, previous->pNext); // создаем новый обьект типа Node, передаем в конструктор данные и у предыдущего элемента берем обьект (адрес) указывающий на следующий элемент односвязного списка
        previous->pNext = newNode;                             // у предыдущего обьекта в его поле pNext добавляем адрес нашего текущего обьекта
        Size++;
    }
}

template <typename T>
void List<T>::insertCell(T data)
{
    Node<T> *previous = this->head;
    Node<T> *current = new Node<T>(data);
    while (previous->pNext != nullptr && previous->pNext->Data < current->Data)
    {
        previous = previous->pNext;
    }
    current->pNext = previous->pNext;
    previous->pNext = current;
    Size++;
}

template <typename T>
void List<T>::insertCelllimiter(T data)
{
    Node<T> *newNode = new Node<T>(data);
    Node<T> *current = this->head;

    while (current->pNext != nullptr && current->pNext->Data < newNode->Data)
    {
        current = current->pNext;
    }

    newNode->pNext = current->pNext;
    current->pNext = newNode;

    if (current->pNext == head) // Если новый элемент должен стать первым
    {
        head = newNode;
    }
}

template <typename T>
void List<T>::sort()
{
    if(head == nullptr || head->pNext == nullptr)               // Если список пуст или состоит из одного элемента, то он уже отсортирован
    {
        return;
    }
    Node<T> *sorted = nullptr;                                  // Инициализируем указатель на отсортированную часть списка
    while (head != nullptr)
    {
        Node<T> *current = head;                                // Запоминаем текущий эллемент
        head = head->pNext;                                     // Перемещаем голову списка на следующий элемент
        if (sorted == nullptr || current->Data < sorted->Data)  // Если отсортированная часть пуста или текущий эллемент меньше первого эллемента в отсортированной части
        {
            current->pNext = sorted;                            // Вставляем текущий элемент в начало отсортированной части
            sorted = current;                                   // Обновляем указатель на отсортированную часть
        }
        else                                                    // Ищем правильное место для вставки текущего элемента в отсортированную часть
        {
            Node<T> *temp = sorted;
            while (temp->pNext != nullptr && current->Data > temp->pNext->Data)
            {
                temp = temp->pNext;
            }
            current->pNext = temp->pNext;                       // Вставляем текущий элемент после temp
            temp->pNext = current;
        }        
    }
    head = sorted;                                              // Обновляем голову списка
}

template <typename T>
void List<T>::clear()
{
    while (Size)
    { // когда Size будет 0 (false) мы выйдем из цикла
        pop_front();
    }
}

template <typename T>
void List<T>::revers()
{
    if (Size <= 1)
        return;
    else
    {
        Node<T> *previous = nullptr;        // 1. Создаем указатель на предыдущий элемент
        Node<T> *current = head;            // 2. Создаем указатель на тукущий элемент
        while (current != nullptr)          // 3. Идем по циклу и ищем голову
        {
            Node<T> *next = current->pNext; // 4. Сохраняем указатель на следующий элемент
            current->pNext = previous;      // 5. Говорим указателю, что его поле pNext теперь NULL
            previous = current;             // 6. Говорим указателю previous, что теперь он указывает на текущий элемент
            current = next;                 // 7. Перемещаем указатель на текущий элемент на следующий элемент
        }                                   // 8. Выходим из цикла
        head = previous;                    // 9. Говорим, что указатель head теперь это указатель на последний элемент
    }
}

template <typename T>
void List<T>::removeAt(int index)
{
    if (index == 0)
        pop_front();
    else
    {                                   // находим предыдущий элемент
        Node<T> *previous = this->head; // создаем временный указатель типа Node и присваиваем ему значение указателя на первый элемент в списке
        for (int i = 0; i < index - 1; i++)
        {                               // цикл, который находит элемент с индексом предшествующему идексу на место которого мы хотим поместить обьект
            previous = previous->pNext; // во временную переменную присваиваем указатель на следующую Node списка
        }
        Node<T> *toDelete = previous->pNext; // переменна нужна для того, чтобы хранить адрес нашего старого элемента на которого указывал наш предыдущий элемент
        previous->pNext = toDelete->pNext;   // предыдущему элементу указываем поле адрес и номер через элемент который мы ходим удалить из списка
        delete toDelete;                     // освобождаем данные старого элемента
        Size--;
    }
}

template <typename T>
void List<T>::Iterate()
{
    int counter = 0;
    Node<T> *current = this->head;
    while (current != nullptr)
    {
        std::cout << " #" << counter << " = " << current->Data;
        current = current->pNext;
        counter++;
    }
    std::cout << std::endl;
}

template <typename T>
bool List<T>::Has_LoopMarking()     // возвращает true если в списке есть цикл, если он есть, то разрываем его
{
    bool has_loop = false;          // предпологаем, что цикла нет
    Node<T> *cell = this->head;     // устанавливаем маркер на голову списка, для прохода по списку
    while (cell->pNext != nullptr)  // проходим по всему списку
    {
        if (cell->pNext->visited)   // проверяем, были ли мы в следующей ячейке
        {
            cell->pNext = nullptr;  // это начало цикла, разрываем цикл
            has_loop = true;        
            break;
        }
        cell = cell->pNext;         // переходим к следующей ячейке
        cell->visited = true;       // помечаем ячейку как пройденную
    }
    cell = this->head;              // еще раз проходим, чтобы снять флажки
    while(cell->pNext != nullptr)
    {
        cell->visited = false;
        cell = cell->pNext;
    }
    return has_loop;                // возвращяем результат
}

template <typename T>
bool List<T>::CycleON(int index)
{
    if (index < 0 || index >= Size)
    {
        return false;                   // Проверяем допустимость индекса
    }

    Node<T> *current = head;
    Node<T> *cycleNode = nullptr;

    for (int i = 0; i < index; i++)     // Достигаем узла, на котором нужно создать цикл
    {
        current = current->pNext;
    }
    cycleNode = current;                // Запоминаем узел для создания цикла

    while (current->pNext != nullptr)   // Достигаем конца списка
    {
        current = current->pNext;
    }

    current->pNext = cycleNode;         // Устанавливаем ссылку на выбранный узел, создавая цикл

    return true;
}

template <typename T>
bool List<T>::Has_LoopRetracing()                // возвращаем true, если в списке есть цикл, разрываем его
{
    Node<T> *cell = this->head;                 // ставим указатель на голову списка, для того, чтобы пройтись по нему
    while (cell->pNext != nullptr)              
    {
        Node<T> *tracer = this->head;           // смотрим, были ли мы в следующей ячейке
        while (tracer != cell)
        {
            if (tracer->pNext == cell->pNext)
            {
                cell->pNext = nullptr;          // это начало цикла разрываем цикл
                return true;                    // возвращяем true
            }
            tracer = tracer->pNext;
        }
        cell = cell->pNext;                     // переходим к следующей ячейке
    }
    return false;                                // Если дошли до этой строки, цикла в списке нет
}

template <typename T>
typename List<T>::Node<T> *List<T>::ReverseList(Node<T> *sentinel) // реверсируем цикл и вовзращяем новое начало списка
{
    Node<T> *prev_cell = nullptr;
    Node<T> *current_cell = sentinel;
    Node<T> *next_cell = nullptr;

    while (current_cell != nullptr)
    {
        next_cell = current_cell->pNext;    // реверсируем ссылку данной ячейки
        current_cell->pNext = prev_cell;
        prev_cell = current_cell;           // переходим к следующей ячейке
        current_cell = next_cell;
    }
    head = prev_cell;                       // возращяем последную найденную ячейку
    return prev_cell;
}

template <typename T>
bool List<T>::Has_LoopReversing()                       // возвращяет true, если в списке есть цикл
{
    if (this->head->pNext == nullptr) { return false; } // если список пуст, цикла в нем нет
    Node<T> *new_sentinel = ReverseList(this->head);    // проходим по всему списку, реверсируя ссылки
    ReverseList(new_sentinel);                          // еще раз проходим по всему списку, восстановить ссылки
    if (new_sentinel == this->head) { return true; }    // если реверсированный список начинается с той же ячейки, что и оригинальный список, значит в нем есть цикл, возвращаем резульат
    return false;                                       // если условия не выполнены, возвращяем false
}

template <typename T>
bool List<T>::hasCycle()
{
    if (head == nullptr || head->pNext == nullptr)      // Проверяем базовые случаи: список пуст или содержит только один элемент
        return false;

                                                        // Инициализируем два указателя: медленный и быстрый
    Node<T> *slow = head;                               // Медленный указатель, двигается по списку с постоянной скоростью
    Node<T> *fast = head->pNext;                        // Быстрый указатель, двигается по списку в два раза быстрее медленного

    while (fast != nullptr && fast->pNext != nullptr)   // Пока быстрый указатель не достиг конца списка или предпоследнего элемента списка
    {
        if (slow == fast)                               // Если медленный и быстрый указатели встречаются, значит, в списке есть цикл
            return true;

        slow = slow->pNext;                             // Перемещаем медленный указатель на следующий элемент списка
        fast = fast->pNext->pNext;                      // Перемещаем быстрый указатель на два элемента вперед
    }

    return false;                                       // Если достигли конца списка (fast равен nullptr), значит, в списке нет цикла
}

template <typename T>
List<T> List<T>::CopyList()
{
    
}

template <typename T>
List<T> List<T>::InsertionSort()
{

}

template <typename T>
T &List<T>::findcell(T data)
{
    Node<T> *current = this->head;
    while (current != nullptr)
    {
        if (current->Data == data)
        {
            std::cout << "Find cell is: " << current->Data << std::endl;
            return current->Data;
        }
        current = current->pNext;
    }
    std::cout << "Not found" << std::endl;
}

template <typename T>
T &List<T>::findcellbefore(T data){
    Node<T> *current = this->head;
    if (current == nullptr)
    {
        std::cout << "Not found" << std::endl;
    }
    while (current->pNext != nullptr)
    {
        if (current->pNext->Data == data)
        {
            std::cout << "Find cell before is: " << current->Data << std::endl;
            return current->Data;
        }
        current = current->pNext;
    }
    std::cout << "Not found" << std::endl;
}

template <typename T>
T &List<T>::findcellbeforelimiter(T data)
{
    Node<T> *limiter = new Node<T>();       // Создаем ограничитель в начале списка, cоздаем пустую ячейку
    limiter->pNext = head;                  // Устанавливаем ограничитель в качестве следующей ячейки для текущего головного элемента
    Node<T> *current = limiter;             // Устанавливаем текущую ячейку на ограничитель
    while (current->pNext != nullptr)
    {
        if (current->pNext->Data == data)
        {
            std::cout << "Find cell before is: " << current->Data << std::endl;
            return current->Data;
        }
        current = current->pNext;
    }

    std::cout << "Not found" << std::endl;
    delete limiter;    // Удаляем ограничитель
    return head->Data; // Возвращаем данные головного элемента
}

template <typename T>
T &List<T>::operator[](const int index)
{
    int counter = 0;               // счетчик, чтобы показать в каком конкретно элементе мы сейчас находимся
    Node<T> *current = this->head; // временный обьект, который отвечает за то, в какой контретно Node мы сейчас с вами находимся, чтобы проверсить адресс следующего элемаента
    while (current != nullptr)
    { // будет работать до тех пор, пока указатель на текущую Node не равен null
        if (counter == index)
        {
            return current->Data;
        }
        current = current->pNext; // переменная, которая ответачает за то, какой у нас на данный момент текщий элемент
        counter++;
    }
    // логика итериции по спису нахождения index и возвращения по этому индексу (номер элемента)
}

