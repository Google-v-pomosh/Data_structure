#pragma once
#include <iostream>
#include <cstdlib> //для использования rand
#include <random>
#include <ctime>


template <typename T>
class DArray
{
private:
    T *array;
    int rows;                                       // переменная для строчек
    int cols;                                       // переменная для столбцов
    int depth;                                      // переменная глубины массива
    int length = 1;                                 // для определения длинны массива
public:
    DArray(int size);                               // конструктор для одномерного массива
    DArray(int numRows, int numCols);               // коснтруктор для двумерного массива
    DArray(int numRows, int numCols, int numDepth); // коснтруктор для трехмерного массива
    ~DArray();                                      // деструктор
    T &operator() (int rows, int cols, int depth);  // оператор для итерации по массиву
    T &operator[] (int index);                      // оператор для итерирования по массиву
    int getRows() {return rows;}                    // метод для получения числа строк
    int getCols() {return cols;}                    // метод для получения числа столбцов
    int getDepth(){return depth;}                   // метод для получения числа глубины
    void overWriting(int size);                                 // производит перезапись на другой массив
    void overWriting(int numRows, int numCols);                 // производит перезапись на другой двумерный массив
    void overWriting(int numRows, int numCols, int numDepth);   // производит перезапись на другой трехмерный массив
    int indexOf(T data);                            // метод для поиска индекса элемента в массиве
    void random();                                  // метод для рандомизации и заполнения массива
    void print3D();                                 // вывод элементов массива 3D
    void print();                                   // вывод элементов массива
    void print2D();                                 // вывод элементов массива 2D
    int Size(){return rows*cols*depth;}             // возвращяет доступный размер массива
    T findMin();                                    // находит минимальное значение в массиве
    T findMax();                                    // находит максимальное значение в массиве
    T findAvegage();                                // находит среднее значение в массиве
    T findMedian();                                 // находит значение по середине у двумерного массива
    void InsertItem(T value, int position);             // Метод для вставки элемента в одномерный массив
    void InsertItem(T value, int row, int col);         // Метод для вставки элемента в двумерный массив
    void InsertItem(T value, int row, int col, int d);  // Метод для вставки элемента в трехмерный массив
};

template <typename T>
DArray<T>::DArray(int size) : rows(1), cols(size), depth(1)
{
    array = new T[size];
}

template <typename T>
DArray<T>::DArray(int numRows, int numCols) : rows(numRows), cols(numCols), depth(1)
{
    array = new T[numRows * numCols];
}

template <typename T>
DArray<T>::DArray(int numRows, int numCols, int numDepth) : rows(numRows), cols(numCols), depth(numDepth)
{
    array = new T[numRows * numCols * numDepth];
}

template <typename T>
DArray<T>::~DArray()
{
    std::cout << "Destructor" << std::endl;
    delete[] array;
}

template <typename T>
T &DArray<T>::operator()(int rows, int cols, int depth)
{
    return array[rows * cols * depth + rows * cols * depth];
}

template <typename T>
T &DArray<T>::operator[](int index)
{
    if (index < 0 || index >= length)
    {
        std::cerr << "Error" << std::endl;
    }
    return array[index];
}

template <typename T>
void DArray<T>::overWriting(int size)
{
    delete[] array;
    array = new T[size];
}

template <typename T>
void DArray<T>::overWriting(int numRows, int numCols)
{
    delete[] array;
    array = new T[numRows*numCols];
}

template <typename T>
void DArray<T>::overWriting(int numRows, int numCols, int numDepth)
{
    delete[] array;
    array = new T[numRows*numCols*numDepth];
}

template <typename T>
int DArray<T>::indexOf(T data)
{
    for (int i = 0; i < rows*cols*depth; ++i)
    {
        if (array[i] == data)
        {
            std::cout << "value found in cell" << std::endl;
            return i;
        }
    }
    std::cout << "value  not found in cell" << std::endl;
    return 0;
}

template <typename T>
void DArray<T>::random()
{
    int totalValues = rows * cols * depth;

    // Заполнить массив array случайными числами от 0 до 100 включительно
    for (int i = 0; i < totalValues; i++)
    {
        (*this)(i / (cols * depth), (i / depth) % cols, i % depth) = std::rand() % 101;
        length++;
    }
}

template <typename T>
void DArray<T>::print3D()
{
    std::cout << "Length: " << length << std::endl;
    for (int i = 0; i < rows; i++) 
    {
    	for (int j = 0; j < cols; j++) 
        {
            for (int k = 0; k < depth; k++)
            {
                std::cout << (*this)(i, j, k) << '\t';
            }
    	}
        std::cout << std::endl;
    }
}

template <typename T>
void DArray<T>::print()
{
    std::cout << "Length: " << length << std::endl;
    for (int i = 0; i < length; i++)
    {
        std::cout << array[i] << '\t';
    }
    std::cout << std::endl;
}

// template <typename T>
// void DArray<T>::print2D()
// {
//     std::cout << "Length: " << length << std::endl;
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             std::cout << array[i* cols + j] << '\t';
//         }
//         std::cout << std::endl;
//     }
// }

template <typename T>
T DArray<T>::findMin()
{
    T min = (*this)(0, 0, 0);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < depth; ++k)
            {
                if ((*this)(i, j, k) < min)
                {
                    min = (*this)(i, j, k);
                }
            }
        }
    }
    return min;
}

template <typename T>
T DArray<T>::findMax()
{
    T max = (*this)(0, 0, 0);
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; ++j)
        {
            for (int k = 0; k < depth; ++k)
            {
                if ((*this)(i, j, k) > max)
                {
                    max = (*this)(i, j, k);
                }
            }
        }
    }
    return max;
}

template <typename T>
T DArray<T>::findAvegage()
{
    T total = static_cast<T>(0);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < depth; ++k)
            {
                total = total + (*this)(i, j, k);
            }
        }
    }
    return total / static_cast<T>(rows * cols * depth);
}

template <typename T>
inline T DArray<T>::findMedian()
{
    T num_larger = static_cast<T>(0);
    T num_smaller = static_cast<T>(0);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < depth; ++k)
            {
                if (array[j] < array[i])
                {
                    num_smaller = num_smaller + 1;
                }
                else if (array[j] > array[i])
                {
                    num_larger = num_larger + 1;
                }
                if (num_larger = num_smaller)
                {
                    return array[i];
                }
            }
        }
    }
}

template <typename T>
inline void DArray<T>::InsertItem(T value, int position)
{
    if (position < 0 || position > length)
    {
        std::cout << "Invalid position!" << std::endl;
        return;
    }

    if (length == rows * cols * depth)
    {
        // Увеличиваем размер массива, если он заполнен
        int newLength = length * 2;
        T *newArray = new T[newLength];
        for (int i = 0; i < length; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        rows = newLength;
    }

    for (int i = length; i > position; i--)
    {
        array[i] = array[i - 1];
    }

    array[position] = value;
    length++;
}

template <typename T>
inline void DArray<T>::InsertItem(T value, int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        std::cout << "Invalid position!" << std::endl;
        return;
    }

    if (length == rows * cols * depth)
    {
        // Увеличиваем размер массива, если он заполнен
        int newLength = length * 2;
        T *newArray = new T[newLength];
        for (int i = 0; i < length; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        rows = newLength;
    }

    int position = row * cols * depth + col * depth;
    for (int i = length; i > position; i--)
    {
        array[i] = array[i - 1];
    }

    array[position] = value;
    length++;
}

template <typename T>
inline void DArray<T>::InsertItem(T value, int row, int col, int d)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols || d < 0 || d >= depth)
    {
        std::cout << "Invalid position!" << std::endl;
        return;
    }

    if (length == rows * cols * depth)
    {
        // Увеличиваем размер массива, если он заполнен
        int newLength = length * 2;
        T *newArray = new T[newLength];
        for (int i = 0; i < length; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        rows = newLength;
    }

    int position = row * cols * depth + col * depth + d;
    for (int i = length; i > position; i--)
    {
        array[i] = array[i - 1];
    }

    array[position] = value;
    length++;
}

// Метод для вставки элемента в одномерный массив
void InsertItem(T value, int position)
{
    
}

// Метод для вставки элемента в двумерный массив
void InsertItem(T value, int row, int col)
{
    
}

// Метод для вставки элемента в трехмерный массив
void InsertItem(T value, int row, int col, int d)
{
    
}
