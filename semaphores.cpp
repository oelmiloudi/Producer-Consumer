#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

// Buffer details
const int N = 5; // Size of the buffer
vector<int> buffer(N);
int in = 0, out = 0;

// Synchronization primitives
mutex mtx;
condition_variable buffer_not_full, buffer_not_empty;
int buffer_count = 0; // Counter for items in the buffer

// Producer function
void producer(int id) {
    while (true) {
        // Produce an item
        int item = rand() % 100;
        cout << "Producer " << id << " produced item: " << item << endl;

        unique_lock<mutex> lock(mtx);

        // Wait until there is space in the buffer
        buffer_not_full.wait(lock, [&] { return buffer_count < N; });

        // Add the item to the buffer
        buffer[in] = item;
        cout << "Producer " << id << " stored item at index: " << in << endl;
        in = (in + 1) % N;
        buffer_count++;

        // Notify consumers that buffer is not empty
        buffer_not_empty.notify_one();

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(500)); // Simulate production time
    }
}

// Consumer function
void consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);

        // Wait until there is something to consume
        buffer_not_empty.wait(lock, [&] { return buffer_count > 0; });

        // Remove an item from the buffer
        int item = buffer[out];
        cout << "Consumer " << id << " consumed item: " << item << " from index: " << out << endl;
        out = (out + 1) % N;
        buffer_count--;

        // Notify producers that buffer is not full
        buffer_not_full.notify_one();

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(500)); // Simulate consumption time
    }
}

int main() {
    // Create producer and consumer threads
    thread producers[2];
    thread consumers[2];

    // Launch producers
    for (int i = 0; i < 2; ++i) {
        producers[i] = thread(producer, i + 1);
    }

    // Launch consumers
    for (int i = 0; i < 2; ++i) {
        consumers[i] = thread(consumer, i + 1);
    }

    // Join threads
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
