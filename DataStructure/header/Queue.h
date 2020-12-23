//
// Created by eugene on 2020-08-12.
//

#pragma once

#include <stdio.h>
#include "../../res/MathUtils.h"

template <class T>
class Queue
{
public:

    //------------- Constructors ------------------//

    Queue();

    // preallocate constructor with user size
    Queue(uint32_t userSize);

    Queue(Queue const& copyQueue);

    // construct from static array
    Queue(T fromArray[], uint32_t size);

    // construct from dynamic array
    Queue(const T* const fromArray, uint32_t size);

    ~Queue();

    //------------- User Level Functions ------------------//

    uint32_t GetSize() const;

    uint32_t GetCapacity() const;

    /*
     * Add a new element at the end of the queue
     * 2 cases:
     * 1 - insert in allocated space
     * 2 - reallocate if we size is at capacity
     */
    void Enqueue(T item);

    T Dequeue();

    /*
     * Pick the element at the end of the queue, do not remove it from queue
     */
    T Rear() const;

    /*
     * Pick the element at the front of the queue, do not remove it from queue
     */
    T Front() const;

private:
    void Allocate_(uint32_t size);

    T* m_data;
    // current size of the queue
    uint32_t m_size = 0;
    // current allocated capacity of physical memory
    uint32_t m_capacity = 0;
    // maximum size that queue can possible be
    const uint32_t m_maxSize = 256;
};
