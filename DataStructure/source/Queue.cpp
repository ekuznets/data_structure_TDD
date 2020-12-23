//
// Created by eugene on 2020-08-12.
//

#include <exception>
#include <sstream>

#include "../header/Queue.h"

// forward declaration is not possible here, since class is using a complete type of this object
struct SizeException : public std::exception
{
    SizeException(uint32_t givenSize, uint32_t const maxSize)
            : m_givenSize(givenSize)
            , m_maxSize(maxSize) {}

    const char* what() const noexcept
    {
        std::stringstream msg;
        msg << "Queue Exception, Provided size - " << m_givenSize
            << " exceeds max size - " << m_maxSize
            << " or is less then 0" << "\n";
        return msg.str().data();
    }
    uint32_t m_givenSize;
    uint32_t const m_maxSize;
};

struct EmptyQueueException : public std::exception
{
    EmptyQueueException() {};

    const char* what() const noexcept
    {
        std::stringstream msg;
        msg << "Queue Exception, Cannot Dequeue because it is empty!\n";
        return msg.str().data();
    }
};

template <class T>
Queue<T>::Queue()
{
    // unless this print comment this should be default
    printf("Queue, Default constructor is called\n");
}

// preallocate constructor with user size
template <class T>
Queue<T>::Queue(uint32_t userSize)
{
    printf("Queue, Size constructor is called\n");
    // validate here before we allocate anything
    if(userSize > m_maxSize || userSize < 0)
    {
        throw SizeException(userSize, m_maxSize);
    }
    m_size = 0;
    if(userSize > 0)
    Allocate_(userSize);
}

template <class T>
Queue<T>::Queue(Queue const& copyQueue)
{
    printf("Queue, Copy Constructor is called\n");
    if(copyQueue.m_capacity > 0)
    {
        Allocate_(copyQueue.m_size);
    }
    m_size = copyQueue.m_size;
    m_capacity = copyQueue.m_capacity;
}

// construct from static array
template <class T>
Queue<T>::Queue(T fromArray[], uint32_t size)
{
    printf("Queue, Static array constructor\n");
    Allocate_(size);
    m_size = size;
}

// construct from dynamic array
template <class T>
Queue<T>::Queue(const T* const fromArray, uint32_t size)
{
    printf("Queue, Dynamic array constructor\n");
    Allocate_(size);
    m_size = size;
}

template <class T>
Queue<T>::~Queue()
{
    printf("Queue, Destructor is called\n");
    if(m_capacity > 0)
    {
        printf("Queue, Freeing the data\n");
        delete[] m_data;
    }
    printf("----------------------------------------\n");;
}

//------------- User Level Functions ------------------//

template <class T>
uint32_t Queue<T>::GetSize() const
{
    return m_size;
}

template <class T>
uint32_t Queue<T>::GetCapacity() const
{
    return m_capacity;
}

/*
 * Add a new element at the end of the queue
 * 2 cases:
 * 1 - insert in allocated space
 * 2 - reallocate if we size is at capacity
 */
template <class T>
void Queue<T>::Enqueue(T item)
{
    printf("Queue, Enqueue is called\n");
    if(m_size == m_capacity)
    Allocate_(m_capacity + 1);
    m_data[m_size] = item;
    m_size++;
}

template <class T>
T Queue<T>::Dequeue()
{
    printf("Queue, Dequeue is called\n");
    if(m_size == 0)
        throw EmptyQueueException();
    m_size--;
    return m_data[0];
}

/*
 * Pick the element at the end of the queue, do not remove it from queue
 */
template <class T>
T Queue<T>::Rear() const
{
    printf("Queue, Rear is called\n");
    return m_data[m_size - 1];
}

/*
 * Pick the element at the front of the queue, do not remove it from queue
 */
template <class T>
T Queue<T>::Front() const
{
    printf("Queue, Front is called\n");
    return m_data[0];
}

template <class T>
void Queue<T>::Allocate_(uint32_t size)
{
    uint32_t memAllocSize = GetNextPowerOfTwo(size);
    printf("Queue, Allocating a new queue with %u elements and Byte size of %lu\n", memAllocSize, memAllocSize * sizeof(T));

    T* newDataSpace = new T[memAllocSize];
    // copy the data out
    if(m_size > 0 && m_data != nullptr)
    {
        memcpy(newDataSpace, m_data, m_size * sizeof(T));
        delete [] m_data;
    }
    m_data = newDataSpace;
    m_capacity = memAllocSize;
}