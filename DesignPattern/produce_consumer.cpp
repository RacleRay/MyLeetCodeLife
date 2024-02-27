#include <condition_variable>
#include <format>
#include <iostream>
#include <mutex>
#include <queue>
#include <stack>
#include <thread>
#include <vector>

std::queue<int> q;
std::mutex mtx;
std::condition_variable cv;

//=================================================================================
//

int pop_obj() {
    std::unique_lock lk(mtx);
    cv.wait(lk, [] { return !q.empty(); });

    auto obj = q.front();
    if (obj != -1) {
        q.pop();
    }
    return obj;
 }

void push_obj(int i) {
  {
    std::unique_lock lk(mtx);
    q.push(i);
  }
  cv.notify_one();
}


void producer() {
    for (int i = 1; i < 100; i++) {
        push_obj(i);
    }
    push_obj(-1);
}

void consumer() {
    while (int obj = pop_obj()) {  // obj 不为0 
        // endl 打印换行然后再 flush ，实际上有点低效
        std::cout << std::format("consumer obj is: {}\n", obj);
        if (obj == -1) {
            break;
        }
    }
}


//=================================================================================
//

int main() {
    std::jthread producer_thread(producer);

    std::vector<std::jthread> consumer_threads;
    for (int i = 0; i < 10; i++) {
        // std::jthread consumer_thread(consumer);
        consumer_threads.emplace_back(consumer);
    }

    return 0;
}