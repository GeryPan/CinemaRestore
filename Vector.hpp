#pragma once
#include <stdexcept>
#include <cassert>


template<typename T>
class Vector
{
    T* arr;     // T = Movie* => arr = Movie**
    unsigned size;
    unsigned capacity;
    bool owns_elements;

    void resize(unsigned new_capacity);
    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other);
    void free();
    void check_index(unsigned index) const;

public:
    Vector();
    Vector(unsigned new_capacity, bool owns);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    Vector(Vector&& other);
    Vector<T>& operator=(Vector&& other);
    void set_ownership(bool own);
    T& operator[](unsigned index);
    const T& operator[](unsigned index) const;

    void push(T value);
    void remove_at(unsigned index);
    unsigned Size() const;
    void clear();
    void pop();
    unsigned indexOf(T value) const;
    ~Vector();
};


template<typename T>
void Vector<T>::resize(unsigned new_capacity)
{
    capacity = new_capacity;
    T* temp = new T[capacity];
    for (unsigned i = 0; i < size; i++)
        temp[i] = arr[i];
    delete[] arr;
    arr = temp;
}

template<typename T>
void Vector<T>::copyFrom(const Vector& other)
{
    assert(other.size <= other.capacity);
    size = other.size;
    capacity = other.capacity;
    owns_elements = other.owns_elements;
    arr = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        arr[i] = owns_elements ? other.arr[i]->clone() : other.arr[i];
    }
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other)
{
    arr = other.arr;
    size = other.size;
    capacity = other.capacity;
    owns_elements = other.owns_elements;

    other.arr = nullptr;
    other.size = 0;
    other.capacity = 0;
    other.owns_elements = false;
}
template<typename T>
void Vector<T>::free()
{
    clear();
    if (arr)
    {
        delete[] arr;
    }
}

template<typename T>
void Vector<T>::check_index(unsigned index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Invalid index!");
}

template<typename T>
Vector<T>::Vector()
{
    arr = new T[capacity];
        capacity = 8;
    size = 0;
}

template<typename T>
Vector<T>::Vector(unsigned new_capacity, bool owns)
{
    capacity = new_capacity;
    arr = new T[capacity];
    size = 0;
    owns_elements = owns;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
    copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(Vector&& other)
{
    moveFrom(std::move(*this));
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
    if (this != &other) {
        free();
        moveFrom(std::move(*this));
    }
    return *this;
}

template<typename T>
void Vector<T>::set_ownership(bool own)
{
    owns_elements = own;
}

template<typename T>
T& Vector<T>::operator[](unsigned index)
{
    check_index(index);
    return arr[index];
}

template<typename T>
const T& Vector<T>::operator[](unsigned index) const
{
    check_index(index);
    return arr[index];
}

template<typename T>
void Vector<T>::push(T value)
{
    if (size >= capacity)
        resize(capacity * 2);
    arr[size++] = value;
}

template<typename T>
void Vector<T>::remove_at(unsigned index)
{
    check_index(index);
    if (owns_elements == true)
        delete arr[index];
    for (unsigned i = index; i < size - 1; i++)
        arr[i] = arr[i + 1];
    size--;
}

template<typename T>
unsigned Vector<T>::Size() const
{
    return size;
}

template<typename T>
void Vector<T>::clear()
{
    if (owns_elements == true)
    {
        for (unsigned i = 0; i < size; i++)
            delete arr[i];
    }
    size = 0;
}

template<typename T>
void Vector<T>::pop()
{
    if (size > 0) {
        if (owns_elements == true)
            delete arr[size - 1];
        size--;
    }
}

template<typename T>
unsigned Vector<T>::indexOf(T value) const
{
    for (unsigned i = 0; i < size; i++)
    {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

template<typename T>
Vector<T>::~Vector()
{
    free();
}