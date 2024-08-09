/// @file tests.cpp
/// @author Abrar Makki
/// @date October 20, 2023

/// 
/// TODO Update the file header with the appropriate information.
///

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

// This is a basic test case example with sections.
// Requires: <no oter functions>
TEST_CASE("Test 0: The Null Test") 
{
    // In this section we test Scenario 1.
    SECTION("Test 0: Empty Truths")
    {
        REQUIRE(true == true);
    }

    // In this section we test Scenario 2.
    SECTION("Test 0: Empty Falsehoods")
    {
        REQUIRE(false == false);
    }
}
// Test for prqueue constructor for native types
// Requires: size(), getRoot(), ~prqueue()
TEST_CASE("Test 1: prqueue constructor") 
{
    prqueue<int> pq;
    SECTION("Empty prqueue int constructor")
    {
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
    }

    prqueue<float> pq2;
    SECTION("Empty prqueue float constructor")
    {
        REQUIRE(pq2.size() == 0);
        REQUIRE(pq2.getRoot() == nullptr);
    }

    prqueue<char> pq3;
    SECTION("Empty prqueue char constructor")
    {
        REQUIRE(pq3.size() == 0);
        REQUIRE(pq3.getRoot() == nullptr);
    }

    prqueue<string> pq4;
    SECTION("Empty prqueue string constructor")
    {
        REQUIRE(pq4.size() == 0);
        REQUIRE(pq4.getRoot() == nullptr);
    }

    prqueue<bool> pq5;
    SECTION("Empty prqueue bool constructor")
    {
        REQUIRE(pq5.size() == 0);
        REQUIRE(pq5.getRoot() == nullptr);
    }

    prqueue<double> pq6;
    SECTION("Empty prqueue double constructor")
    {
        REQUIRE(pq6.size() == 0);
        REQUIRE(pq6.getRoot() == nullptr);
    }

    prqueue<long> pq7;
    SECTION("Empty prqueue long constructor")
    {
        REQUIRE(pq7.size() == 0);
        REQUIRE(pq7.getRoot() == nullptr);
    }

    prqueue<long long> pq8;
    SECTION("Empty prqueue long long constructor")
    {
        REQUIRE(pq8.size() == 0);
        REQUIRE(pq8.getRoot() == nullptr);
    }

    prqueue<short> pq9;
    SECTION("Empty prqueue short constructor")
    {
        REQUIRE(pq9.size() == 0);
        REQUIRE(pq9.getRoot() == nullptr);
    }

    prqueue<unsigned int> pq10;
    SECTION("Empty prqueue unsigned int constructor")
    {
        REQUIRE(pq10.size() == 0);
        REQUIRE(pq10.getRoot() == nullptr);
    }
}

// Test for enqueue for native types
// Requires: size(), toString(),  ~prqueue()
TEST_CASE("Test 2: enqueue") {
    prqueue<char> pq;
    prqueue<int> pq2;
    prqueue<string> pq3;
    prqueue<float> pq4;
    prqueue<bool> pq5;
    SECTION("enqueue chars") {
        pq.enqueue('a', 1);
        pq.enqueue('b', 2);
        pq.enqueue('c', 3);
        pq.enqueue('d', 4);
        pq.enqueue('e', 4);
        pq.enqueue('f', 4);
        pq.enqueue('z', 0);
        pq.enqueue('y', -1);
        pq.enqueue('x', -2);
        pq.enqueue('w', -3);
        pq.enqueue('v', -3);
        REQUIRE(pq.size() == 11);
        REQUIRE(pq.toString() == "-3 value: w\n-3 value: v\n-2 value: x\n-1 value: y\n0 value: z\n1 value: a\n2 value: b\n3 value: c\n4 value: d\n4 value: e\n4 value: f\n");
    }

    SECTION("enqueue ints") {
        pq2.enqueue(1, 1);
        pq2.enqueue(2, 2);
        pq2.enqueue(3, 3);
        pq2.enqueue(4, 4);
        pq2.enqueue(5, 4);
        pq2.enqueue(6, 4);
        pq2.enqueue(26, 0);
        pq2.enqueue(25, -1);
        pq2.enqueue(24, -2);
        pq2.enqueue(23, -3);
        pq2.enqueue(22, -3);
        REQUIRE(pq2.size() == 11);
        REQUIRE(pq2.toString() == "-3 value: 23\n-3 value: 22\n-2 value: 24\n-1 value: 25\n0 value: 26\n1 value: 1\n2 value: 2\n3 value: 3\n4 value: 4\n4 value: 5\n4 value: 6\n");
    }

    SECTION("enqueue strings") {
        pq3.enqueue("second", 2);
        pq3.enqueue("fifth", 5);
        pq3.enqueue("third", 3);
        pq3.enqueue("first", 1);
        pq3.enqueue("fourth", 4);
        pq3.enqueue("sixth", 5);
        pq3.enqueue("zeroeth", -1000);
        REQUIRE(pq3.size() == 7);
        REQUIRE(pq3.toString() == "-1000 value: zeroeth\n1 value: first\n2 value: second\n3 value: third\n4 value: fourth\n5 value: fifth\n5 value: sixth\n");
    }

    SECTION("enqueue floats") {
        pq4.enqueue(1.2, 1);
        pq4.enqueue(2.3, 2);
        pq4.enqueue(3.4, 3);
        pq4.enqueue(4.5, 4);
        pq4.enqueue(5.6, 4);
        pq4.enqueue(6.7, 4);
        pq4.enqueue(26.2741, 0);
        pq4.enqueue(25.313, -1);
        pq4.enqueue(24.2134, -2);
        pq4.enqueue(23.2643, -3);
        pq4.enqueue(22.2562, -3);
        REQUIRE(pq4.size() == 11);
        REQUIRE(pq4.toString() == "-3 value: 23.2643\n-3 value: 22.2562\n-2 value: 24.2134\n-1 value: 25.313\n0 value: 26.2741\n1 value: 1.2\n2 value: 2.3\n3 value: 3.4\n4 value: 4.5\n4 value: 5.6\n4 value: 6.7\n");
    }

    SECTION("enqueue bools") {
        pq5.enqueue(true, 1);
        pq5.enqueue(false, 2);
        pq5.enqueue(true, 3);
        pq5.enqueue(false, 4);
        pq5.enqueue(true, 4);
        pq5.enqueue(false, 4);
        pq5.enqueue(true, 0);
        pq5.enqueue(false, -1);
        pq5.enqueue(true, -2);
        pq5.enqueue(false, -3);
        pq5.enqueue(true, -3);
        REQUIRE(pq5.size() == 11);
        REQUIRE(pq5.toString() == "-3 value: 0\n-3 value: 1\n-2 value: 1\n-1 value: 0\n0 value: 1\n1 value: 1\n2 value: 0\n3 value: 1\n4 value: 0\n4 value: 1\n4 value: 0\n");
    }
}
// Test for size for native types
// Requires: enqueue(), size(),  ~prqueue()
TEST_CASE("Test 3: size") {
    map<int, vector<int>> input;
    prqueue<int> pq;
    int sz = 10;
    int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
    int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
    for (int i = 0; i < sz; i++) {
        REQUIRE(pq.size() == i);
        pq.enqueue(values[i], priorities[i]);
        input[priorities[i]].push_back(values[i]);
    }
    REQUIRE(pq.size() == sz);

    map<int, vector<char>> input2;
    prqueue<char> pq2;
    int sz2 = 10;
    char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    int priorities2[sz2] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
    for (int i = 0; i < sz2; i++) {
        REQUIRE(pq2.size() == i);
        pq2.enqueue(values2[i], priorities2[i]);
        input2[priorities2[i]].push_back(values2[i]);
    }
    REQUIRE(pq2.size() == sz2);

    map<int, vector<string>> input3;
    prqueue<string> pq3;
    int sz3 = 10;
    string values3[sz3] = {"lol", "hello", "world", "this", "is", "a", "test", "of", "the", "size"};
    int priorities3[sz3] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
    for (int i = 0; i < sz3; i++) {
        REQUIRE(pq3.size() == i);
        pq3.enqueue(values3[i], priorities3[i]);
        input3[priorities3[i]].push_back(values3[i]);
    }
    REQUIRE(pq3.size() == sz3);

    map<int, vector<float>> input4;
    prqueue<float> pq4;
    int sz4 = 10;
    float values4[sz4] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 26.2741, 25.313, 24.2134, 23.2643};
    int priorities4[sz4] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
    for (int i = 0; i < sz4; i++) {
        REQUIRE(pq4.size() == i);
        pq4.enqueue(values4[i], priorities4[i]);
        input4[priorities4[i]].push_back(values4[i]);
    }
    REQUIRE(pq4.size() == sz4);
}
// Test for toString for mixture
// Requires: enqueue(), getRoot(), ~prqueue(), size(), toString()
TEST_CASE("Test 4: toString") {
    SECTION ("toString for ints") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        int sz = 10;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            input[priorities[i]].push_back(values[i]);
        }
        stringstream ss;
        for (const auto& p : input) {
            int priority = p.first;
            vector<int> values = p.second;
            for (int value : values) {
                ss << priority << " value: " << value << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());
        REQUIRE(pq.size() == sz);
    }
    SECTION("toString for chars") {
        map<int, vector<char>> input2;
        prqueue<char> pq2;
        int sz2 = 10;
        char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities2[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz2; i++) {
            pq2.enqueue(values2[i], priorities2[i]);
            input2[priorities2[i]].push_back(values2[i]);
        }
        stringstream ss2;
        for (const auto& p : input2) {
            int priority = p.first;
            vector<char> values = p.second;
            for (size_t i = 0; i < values.size(); i++) {
                ss2 << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq2.toString() == ss2.str());
        REQUIRE(pq2.size() == sz2);
    }
    SECTION("toString for strings") {
        map<int, vector<string>> input3;
        prqueue<string> pq3;
        int sz3 = 10;   
        string values3[sz3] = {"lol", "hello", "world", "this", "is", "a", "test", "of", "the", "toString"};
        int priorities3[sz3] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz3; i++) {
            pq3.enqueue(values3[i], priorities3[i]);
            input3[priorities3[i]].push_back(values3[i]);
        }
        stringstream ss3;
        for (const auto& p : input3) {
            int priority = p.first;
            vector<string> values = p.second;
            for (size_t i = 0; i < values.size(); i++) {
                ss3 << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq3.toString() == ss3.str());
        REQUIRE(pq3.size() == sz3);
    }
}
// Test for clear for native types
// Requires: enqueue(), clear(), size(), getRoot(), ~prqueue(), toString()
TEST_CASE("Test 5: clear") {
    SECTION ("clear for ints") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        int sz = 10;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            input[priorities[i]].push_back(values[i]);
        }
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.toString() == "");
    }
    SECTION ("clear for chars") {
        map<int, vector<char>> input2;
        prqueue<char> pq2;
        int sz2 = 10;
        char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities2[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz2; i++) {
            pq2.enqueue(values2[i], priorities2[i]);
            input2[priorities2[i]].push_back(values2[i]);
        }
        pq2.clear();
        REQUIRE(pq2.size() == 0);
        REQUIRE(pq2.getRoot() == nullptr);
        REQUIRE(pq2.toString() == "");
    }
    SECTION ("clear for strings") {
        map<int, vector<string>> input3;
        prqueue<string> pq3;
        int sz3 = 10;   
        string values3[sz3] = {"lol", "hello", "world", "this", "is", "a", "test", "of", "the", "clear"};
        int priorities3[sz3] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz3; i++) {
            pq3.enqueue(values3[i], priorities3[i]);
            input3[priorities3[i]].push_back(values3[i]);
        }
        pq3.clear();
        REQUIRE(pq3.size() == 0);
        REQUIRE(pq3.getRoot() == nullptr);
        REQUIRE(pq3.toString() == "");
    }
}
// Test for assignment operator overload for native types
// Requires: enqueue(), size(), getRoot(), ~prqueue(), toString()
TEST_CASE("Test 6: assignment operator overload") {
    SECTION ("assignment operator overload for ints") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        int sz = 10;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            input[priorities[i]].push_back(values[i]);
        }
        prqueue<int> pq2;
        pq2 = pq;
        REQUIRE(pq2.size() == pq.size());
        REQUIRE(pq2.getRoot() != pq.getRoot());
        REQUIRE(pq2.toString() == pq.toString());
    }

    SECTION("assignment operator overload for chars") {
        map<int, vector<char>> input2;
        prqueue<char> pq3;
        int sz2 = 10;
        char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities2[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz2; i++) {
            pq3.enqueue(values2[i], priorities2[i]);
            input2[priorities2[i]].push_back(values2[i]);
        }
        prqueue<char> pq4;
        pq4 = pq3;
        REQUIRE(pq4.size() == pq3.size());
        REQUIRE(pq4.getRoot() != pq3.getRoot());
        REQUIRE(pq4.toString() == pq3.toString());
    }

    SECTION("assignment operator overload for strings") {
        map<int, vector<string>> input3;
        prqueue<string> pq5;
        int sz3 = 10;   
        string values3[sz3] = {"lol", "hello", "world", "this", "is", "a", "test", "of", "the", "assignment operator overload"};
        int priorities3[sz3] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz3; i++) {
            pq5.enqueue(values3[i], priorities3[i]);
            input3[priorities3[i]].push_back(values3[i]);
        }
        prqueue<string> pq6;
        pq6 = pq5;
        REQUIRE(pq6.size() == pq5.size());
        REQUIRE(pq6.getRoot() != pq5.getRoot());
        REQUIRE(pq6.toString() == pq5.toString());
    }
}
// Test for next and begin for various trees
// Requires: next(), begin(), getRoot(), ~prqueue(), enqueue()
TEST_CASE("Test 7: begin and next") {
    SECTION("next and begin for small tree, no duplicates") {
        prqueue<int> pq;
        pq.enqueue(1, 1);
        pq.enqueue(2, 2);
        pq.enqueue(3, 3);
        pq.enqueue(4, 4);
        pq.begin();
        int priority = 0;
        int value = 0;
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 1);
        REQUIRE(value == 1);
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == 2);
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(priority == 3);
        REQUIRE(value == 3);
        REQUIRE(pq.next(value, priority) == false);
        REQUIRE(priority == 4);
        REQUIRE(value == 4);
    }
    SECTION("next and begin for small tree, duplicates") {
        prqueue<char> pq2;
        pq2.enqueue('e', 4);
        pq2.enqueue('f', 4);
        pq2.enqueue('d', 3);
        pq2.enqueue('b', 2);
        pq2.enqueue('c', 3);
        pq2.enqueue('a', 0);
        pq2.enqueue('g', 4);
        pq2.enqueue('h', 4);
        pq2.enqueue('i', 5);
        pq2.enqueue('j', 5);
        pq2.begin();
        int priority = 0;
        char value = 0;
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 0);
        REQUIRE(value == 'a');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 2);
        REQUIRE(value == 'b');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 3);
        REQUIRE(value == 'd');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 3);
        REQUIRE(value == 'c');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 4);
        REQUIRE(value == 'e');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 4);
        REQUIRE(value == 'f');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 4);
        REQUIRE(value == 'g');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 4);
        REQUIRE(value == 'h');
        REQUIRE(pq2.next(value, priority) == true);
        REQUIRE(priority == 5);
        REQUIRE(value == 'i');
        REQUIRE(pq2.next(value, priority) == false);
        REQUIRE(priority == 5);
        REQUIRE(value == 'j');
    }
    SECTION("next and begin for big tree with dupes") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        int sz = 90;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666, 19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3, -1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            input[priorities[i]].push_back(values[i]);
        }
        pq.begin();
        int priority = 0;
        int value = 0;
        for (int i = 0; i < sz - 1; i++) {
            REQUIRE(pq.next(value, priority) == true);
        }
        REQUIRE(pq.next(value, priority) == false);
    }
}
// Test for dequeue for native types
// Requires: enqueue(), dequeue(), size(), getRoot(), ~prqueue(), toString()
TEST_CASE("Test 8: dequeue") {
    SECTION("dequeue for ints") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        int sz = 10;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            input[priorities[i]].push_back(values[i]);
        }
        stringstream ss;
        for (const auto& p : input) {
            int priority = p.first;
            vector<int> values = p.second;
            for (int value : values) {
                ss << priority << " value: " << value << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());
        REQUIRE(pq.size() == sz);
        REQUIRE(pq.dequeue() == 744);
        REQUIRE(pq.dequeue() == 19);
        REQUIRE(pq.dequeue() == 391);
        REQUIRE(pq.dequeue() == 46);
        REQUIRE(pq.dequeue() == 103);
        REQUIRE(pq.dequeue() == 666);
        REQUIRE(pq.dequeue() == 942);
        REQUIRE(pq.dequeue() == 822);
        REQUIRE(pq.dequeue() == 439);
        REQUIRE(pq.dequeue() == 541);
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.toString() == "");
    }
    SECTION("dequeue for chars") {
        map<int, vector<char>> input2;
        prqueue<char> pq2;
        int sz2 = 10;
        char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities2[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz2; i++) {
            pq2.enqueue(values2[i], priorities2[i]);
            input2[priorities2[i]].push_back(values2[i]);
        }
        stringstream ss2;
        for (const auto& p : input2) {
            int priority = p.first;
            vector<char> values = p.second;
            for (size_t i = 0; i < values.size(); i++) {
                ss2 << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq2.toString() == ss2.str());
        REQUIRE(pq2.size() == sz2);
        REQUIRE(pq2.dequeue() == 'a');
        REQUIRE(pq2.dequeue() == 'b');
        REQUIRE(pq2.dequeue() == 'c');
        REQUIRE(pq2.dequeue() == 'd');
        REQUIRE(pq2.dequeue() == 'e');
        REQUIRE(pq2.dequeue() == 'f');
        REQUIRE(pq2.dequeue() == 'g');
        REQUIRE(pq2.dequeue() == 'h');
        REQUIRE(pq2.dequeue() == 'i');
        REQUIRE(pq2.dequeue() == 'j');
        REQUIRE(pq2.size() == 0);
        REQUIRE(pq2.getRoot() == nullptr);
        REQUIRE(pq2.toString() == "");
    }
}
// Test for peek
// Requires: enqueue(), peek(), size(), getRoot(), ~prqueue(), toString()
TEST_CASE("Test 9: peek") {
    SECTION("peek for ints") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        int sz = 10;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        int answers[sz] = {744, 19, 391, 46, 103, 666, 942, 822, 439, 541};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            input[priorities[i]].push_back(values[i]);
        }
        stringstream ss;
        for (const auto& p : input) {
            int priority = p.first;
            vector<int> values = p.second;
            for (int value : values) {
                ss << priority << " value: " << value << endl;
            }
        }
        for (int i = 0; i < sz; i++) {
            REQUIRE(pq.peek() == answers[i]);
            pq.dequeue();
        }
    }
    SECTION("peek for chars") {
        map<int, vector<char>> input2;
        prqueue<char> pq2;
        int sz2 = 10;
        char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities2[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        char answers2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        for (int i = 0; i < sz2; i++) {
            pq2.enqueue(values2[i], priorities2[i]);
            input2[priorities2[i]].push_back(values2[i]);
        }
        stringstream ss2;
        for (const auto& p : input2) {
            int priority = p.first;
            vector<char> values = p.second;
            for (size_t i = 0; i < values.size(); i++) {
                ss2 << priority << " value: " << values[i] << endl;
            }
        }
        for (int i = 0; i < sz2; i++) {
            REQUIRE(pq2.peek() == answers2[i]);
            pq2.dequeue();
        }
    }
}
//test for equals operator
// Requires: enqueue(), equals(), size(), getRoot(), ~prqueue(), toString()
TEST_CASE("Test 10: equals") {
    SECTION("equals for ints") {
        map<int, vector<int>> input;
        prqueue<int> pq;
        prqueue<int> pq2;
        int sz = 10;
        int values[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        int values2[sz] = {19, 103, 391, 942, 541, 46, 744, 822, 439, 666};
        int priorities2[sz] = {-1, 2, 0, 4, 5, 0, -7, 4, 4, 3};
        for (int i = 0; i < sz; i++) {
            pq.enqueue(values[i], priorities[i]);
            pq2.enqueue(values2[i], priorities2[i]);
            input[priorities[i]].push_back(values[i]);
        }
        stringstream ss;
        for (const auto& p : input) {
            int priority = p.first;
            vector<int> values = p.second;
            for (int value : values) {
                ss << priority << " value: " << value << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());
        REQUIRE(pq.size() == sz);
        REQUIRE(pq2.toString() == ss.str());
        REQUIRE(pq2.size() == sz);
        REQUIRE(pq == pq2);
        REQUIRE(pq2 == pq);
        pq2.dequeue();
        REQUIRE_FALSE(pq == pq2);
        REQUIRE_FALSE(pq2 == pq);
    }
    SECTION("equals for chars") {
        map<int, vector<char>> input2;
        prqueue<char> pq3;
        prqueue<char> pq4;
        int sz2 = 10;
        char values2[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities2[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        char values3[sz2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        int priorities3[sz2] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < sz2; i++) {
            pq3.enqueue(values2[i], priorities2[i]);
            pq4.enqueue(values3[i], priorities3[i]);
            input2[priorities2[i]].push_back(values2[i]);
        }
        stringstream ss2;
        for (const auto& p : input2) {
            int priority = p.first;
            vector<char> values = p.second;
            for (size_t i = 0; i < values.size(); i++) {
                ss2 << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq3.toString() == ss2.str());
        REQUIRE(pq3.size() == sz2);
        REQUIRE(pq4.toString() == ss2.str());
        REQUIRE(pq4.size() == sz2);
        REQUIRE(pq3 == pq4);
        REQUIRE(pq4 == pq3);
        pq4.dequeue();
        REQUIRE_FALSE(pq3 == pq4);
        REQUIRE_FALSE(pq4 == pq3);
    }
}

