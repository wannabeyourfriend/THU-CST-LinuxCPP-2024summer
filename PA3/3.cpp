#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cassert>

// 定义任务优先级结构体
struct Task {
    int priority;
    std::function<void()> func;

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

// 进程池类模板
template<typename T>
class ProcessPool {
public:
    ProcessPool(size_t numProcesses);
    ~ProcessPool();
    
    void addTask(T task, int priority);
    void start();

private:
    void workerThread();
    
    size_t numProcesses;
    std::vector<std::thread> workers;
    std::priority_queue<Task> taskQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool stop;
};

// 进程池构造函数
template<typename T>
ProcessPool<T>::ProcessPool(size_t numProcesses)
    : numProcesses(numProcesses), stop(false) {}

// 进程池析构函数
template<typename T>
ProcessPool<T>::~ProcessPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    cv.notify_all();
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

// 添加任务到任务队列
template<typename T>
void ProcessPool<T>::addTask(T task, int priority) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push({priority, task});
    }
    cv.notify_one();
}

// 启动进程池
template<typename T>
void ProcessPool<T>::start() {
    for (size_t i = 0; i < numProcesses; ++i) {
        workers.emplace_back(&ProcessPool<T>::workerThread, this);
    }
}

// 工作线程执行函数
template<typename T>
void ProcessPool<T>::workerThread() {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this] { return stop || !taskQueue.empty(); });
            if (stop && taskQueue.empty()) {
                return;
            }
            task = taskQueue.top();
            taskQueue.pop();
        }
        task.func();
    }
}

// 测试进程池
int main() {
    ProcessPool<std::function<void()>> pool(4);

    pool.start();

    pool.addTask([]() { std::cout << "Task 1 (Priority 1)" << std::endl; }, 1);
    pool.addTask([]() { std::cout << "Task 2 (Priority 3)" << std::endl; }, 3);
    pool.addTask([]() { std::cout << "Task 3 (Priority 2)" << std::endl; }, 2);

    sleep(1); // 等待任务完成
    return 0;
}
