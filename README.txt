Producer-Consumer Problem Using C++11 Synchronization Primitives
Author: Omar El Miloudi
Created Date: 11/12/2024

Overview:

This project is a C++ implementation of the classic Producer-Consumer problem using modern C++11 threading constructs. The program utilizes std::thread, std::mutex, and std::condition_variable to efficiently manage the production and consumption of items in a shared buffer.

The Producer-Consumer problem is a classic example of a multi-thread synchronization problem where:
    Producers generate data and place it in a buffer.
    Consumers consume data from the buffer.
    Proper synchronization is necessary to ensure that the buffer is not accessed by multiple threads simultaneously, leading to data corruption.

This solution ensures:
    Mutual exclusion when accessing the shared buffer.
    Synchronization between producers and consumers using condition variables.
    Efficient handling of the buffer, preventing race conditions.

Features:
    1. Multi-threaded implementation using C++11.
    2. Uses condition variables and mutexes to ensure proper synchronization.
    3. Adjustable buffer size and number of producers/consumers.
    4. Demonstrates concepts like thread safety, critical sections, and inter-thread communication.

High-Level Design:

1. Producer:
    Continuously produces items (random integers).
    Waits if the buffer is full using a condition variable (buffer_not_full).
    Adds produced items to the buffer and notifies consumers.

2. Consumer:
    Continuously consumes items from the buffer.
    Waits if the buffer is empty using a condition variable (buffer_not_empty).
    Removes items from the buffer and notifies producers.

3. Shared Buffer:
    A fixed-size vector is used to simulate the buffer.
    Two condition variables control access:
        - buffer_not_full - ensures producers wait when the buffer is full.
        - buffer_not_empty - ensures consumers wait when the buffer is empty.
    A mutex (mtx) protects access to shared resources, ensuring mutual exclusion.


Low-Level Details:

    Mutex:
        - Ensures that only one thread can access or modify the buffer at a time.
    Condition Variables:
        - buffer_not_full: Signals producers when there is space in the buffer.
        - buffer_not_empty: Signals consumers when there is data to consume.
    Thread Creation:
        - The program creates multiple producer and consumer threads using std::thread.
        - Each producer and consumer thread runs continuously in an infinite loop.
    Lambda Expressions:
        - Used in conjunction with condition variables to define wait conditions.

Requirements:

    1. Operating System: macOS (tested on macOS with Xcode Command Line Tools)
    2. Compiler: g++ (supporting C++11 or later)
    3. Tools: Terminal

How to Compile and Run:

    1. Open Terminal on your macOS system.
    2. Compile the program using the following command: "g++ -std=c++11 semaphores.cpp -o producerConsumer -pthread"
    3. Run the program using the command: "./producerConsumer"

Explanation of Output:
    Producers generate random items and place them in the buffer.
    Consumers consume items from the buffer.
    The output shows the buffer index at which items are produced and consumed.

Contact Information:

    If you have any questions or suggestions, please contact the author at:

    Omar El Miloudi
    Email: [oelmiloudi123@gmail.com]