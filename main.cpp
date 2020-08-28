#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "datastructure/header/Queue.h"
#include <iostream>

TEST_CASE("Testing Queue Size", "[Queue Size]")
{
    SECTION("Valid size Queue Test will be 0") {
        Queue<uint64_t> q1(0);
        REQUIRE(q1.GetSize() == 0);

        Queue<uint64_t> q2(10);
        REQUIRE(q2.GetSize() == 0);

        Queue<uint64_t> q3;
        REQUIRE(q3.GetSize() == 0);
    }


    SECTION("Invalid size Queue Test") {
        try {
            Queue<uint64_t> q1(-1);
            REQUIRE(false);
        }
        catch (std::exception const &e) {
            printf("Caught an exception - %s\n", e.what());
            REQUIRE(true);
        }
    }

    SECTION("Exceed maximum Queue Test") {
        try {
            Queue<char> q1(257);
            REQUIRE(false);
        }
        catch (std::exception const &e) {
            printf("Caught an exception - %s\n", e.what());
            REQUIRE(true);
        }
    }

    SECTION("Initialize from the simple data type")
    {
        const int size = 5;
        uint32_t arr[] = {1,2,3,4,5};
        const uint32_t* arrDynamic = new uint32_t[size];
        memcpy(&arrDynamic, &arr, size);

        Queue<uint32_t> q1(arr, size);
        REQUIRE(q1.GetSize() == size);

        Queue<uint32_t> q2(arrDynamic, size);
        REQUIRE(q2.GetSize() == size);
    }

    SECTION("Test that Enqueue/Dequeue increase the size of the queue") {
        const int size = 3;
        int arr[] = {1,2,3};
        Queue<int> q1(arr, size);

        REQUIRE(q1.GetSize() == 3);
        q1.Enqueue(101);
        REQUIRE(q1.GetSize() == 4);
        q1.Enqueue(102);
        REQUIRE(q1.GetSize() == 5);
        q1.Enqueue(103);
        REQUIRE(q1.GetSize() == 6);

        int value = -1;

        value = q1.Dequeue();
        REQUIRE(q1.GetSize() == 5);
        value = q1.Dequeue();
        REQUIRE(q1.GetSize() == 4);
        value = q1.Dequeue();
        REQUIRE(q1.GetSize() == 3);
        value = q1.Dequeue();
        REQUIRE(q1.GetSize() == 2);
        value = q1.Dequeue();
        REQUIRE(q1.GetSize() == 1);
        value = q1.Dequeue();
        REQUIRE(q1.GetSize() == 0);
    }

    SECTION("Test Dequeue of an empty queue throws exception") {
        Queue<uint64_t> q1(0);
        REQUIRE(q1.GetSize() == 0);

        try {
            uint64_t value = q1.Dequeue();
            printf("value is %llu\n", value);
            REQUIRE(false);
        }
        catch (std::exception const& e) {
            printf("Caught an exception - %s\n", e.what());
        }
        // queue still should be 0 size
        REQUIRE(q1.GetSize() == 0);
    }

}

TEST_CASE("Copy the Queue", "[Queue Copy]")
{
    SECTION("Copy Queue Test with equal operator") {
        Queue<int> q1;
        Queue<int> q2 = q1;
        REQUIRE(q2.GetSize() == 0);
        REQUIRE(q2.GetCapacity() == GetNextPowerOfTwo(0));

        Queue<int> q3(10);
        Queue<int> q4 = q3;
        REQUIRE(q4.GetSize() == 0);
        REQUIRE(q4.GetCapacity() == GetNextPowerOfTwo(10));

        //add a data verification test
    }

    SECTION("Copy Queue Test with Copy Constructor") {
        Queue<int> q1;
        Queue<int> q2(q1);
        REQUIRE(q2.GetSize() == 0);
        REQUIRE(q2.GetSize() == GetNextPowerOfTwo(0));

        Queue<int> q3(10);
        Queue<int> q4(q3);
        REQUIRE(q4.GetSize() == 0);
        REQUIRE(q4.GetCapacity() == GetNextPowerOfTwo(10));

        //add a data verification test
    }
}

TEST_CASE("Insert into and verify the remove", "[Enqueue and dequeue values test]")
{
    SECTION("Queue test Enqueue/rear simple") {
        Queue<int> q1;
        q1.Enqueue(10);
        REQUIRE(q1.Rear() == 10);
    }

    SECTION("Queue test Front/Rear logic") {
        Queue<int> q1;
        q1.Enqueue(11);
        // After one insert Rear and Front should be the same
        REQUIRE(q1.Rear() == q1.Front());
        q1.Enqueue(12);
        // After second insert Rear and Front should NOT be the same
        REQUIRE(q1.Rear() != q1.Front());
    }

    SECTION("Queue test Enqueue Front/Rear, data integrity") {
        Queue<int> q1;
        q1.Enqueue(10);
        REQUIRE(q1.Rear() == 10);
        REQUIRE(q1.Front() == 10);
        q1.Enqueue(20);
        REQUIRE(q1.Rear() == 20);
        REQUIRE(q1.Front() == 10);
        q1.Enqueue(30);
        REQUIRE(q1.Rear() == 30);
        REQUIRE(q1.Front() == 10);
        q1.Enqueue(40);
        REQUIRE(q1.Rear() == 40);
        REQUIRE(q1.Front() == 10);
        q1.Enqueue(50);
        REQUIRE(q1.Rear() == 50);
        REQUIRE(q1.Front() == 10);
        q1.Enqueue(66);
        REQUIRE(q1.Rear() == 66);
        REQUIRE(q1.Front() == 10);
    }

    // add dequeue test
    SECTION("Queue test Dequeue Front/Rear, data integrity") {
//        const int size = 9;
//        uint32_t arr[] = {1,2,3,4,5};
//        Queue<int> q1;
    }
}

TEST_CASE("Capacity, memory allocation", "[Test that we initialize correct capacity]")
{
    SECTION("Capacity on Init") {
        Queue<uint32_t> q1;
        REQUIRE(q1.GetCapacity() == 0);

        Queue<uint32_t> q2(10);
        REQUIRE(q2.GetCapacity() == GetNextPowerOfTwo(10));

        const int size = 5;
        uint32_t arr[] = {1, 2, 3, 4, 5};
        uint32_t *arrDynamic = new uint32_t[size];
        memcpy(arrDynamic, arr, size);

        Queue<uint32_t> q3(arr, size);
        REQUIRE(q3.GetCapacity() == GetNextPowerOfTwo(size));

        Queue<uint32_t> q4(arrDynamic, size);
        REQUIRE(q4.GetCapacity() == GetNextPowerOfTwo(size));
    }

    SECTION("Enqueue Capacity extension") {
        Queue<uint32_t> q1;
        REQUIRE(q1.GetCapacity() == 0);
        q1.Enqueue(10);
        REQUIRE(q1.GetCapacity() == 1);
        q1.Enqueue(20);
        REQUIRE(q1.GetCapacity() == 2);
        q1.Enqueue(30);
        REQUIRE(q1.GetCapacity() == 4);
        q1.Enqueue(40);
        REQUIRE(q1.GetCapacity() == 4);
        q1.Enqueue(50);
        REQUIRE(q1.GetCapacity() == 8);

        uint32_t arr[] = {1, 2, 3, 4, 5, 6, 7};
        Queue<uint32_t> q2(arr, 7);
        REQUIRE(q2.GetCapacity() == 8);
        q2.Enqueue(10);
        REQUIRE(q2.GetCapacity() == 8);
        q2.Enqueue(20);
        REQUIRE(q2.GetCapacity() == 16);
    }

    // add simple test that Dequeue does not reduce capacity
}

TEST_CASE("Generate next number for power of two", "[Make sure we only allocate power of 2]")
{
    // 0 case = still allocate 0
    REQUIRE(GetNextPowerOfTwo(0) == 0);
    // 2^0 case = still allocate 2^0
    REQUIRE(GetNextPowerOfTwo(1) == 1<<0);
    // 2^1 case = still allocate 2^1
    REQUIRE(GetNextPowerOfTwo(2) == 1<<1);
    // 3 case = still allocate 2^2
    REQUIRE(GetNextPowerOfTwo(3) == 1<<2);
    // 9 case = still allocate 2^4
    REQUIRE(GetNextPowerOfTwo(9) == 1<<4);
    // 16 case = still allocate 2^4 = maximum
    REQUIRE(GetNextPowerOfTwo(16) == 1<<4);
    // 100 case = still allocate 2^7
    REQUIRE(GetNextPowerOfTwo(100) == 1<<7);
}































