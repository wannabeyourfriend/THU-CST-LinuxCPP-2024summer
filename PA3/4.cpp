#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <atomic>
#include <stdexcept>

template<typename T>
class Mutex {
public:
    Mutex() { pthread_mutex_init(&mutex_, nullptr); }
    ~Mutex() { pthread_mutex_destroy(&mutex_); }
    
    void lock() { pthread_mutex_lock(&mutex_); }
    void unlock() { pthread_mutex_unlock(&mutex_); }
    
private:
    pthread_mutex_t mutex_;
};

template<typename T>
class Semaphore {
public:
    Semaphore(int value = 0) : value_(value) { sem_init(&sem_, 0, value); }
    ~Semaphore() { sem_destroy(&sem_); }
    
    void wait() { sem_wait(&sem_); }
    void signal() { sem_post(&sem_); }
    
private:
    sem_t sem_;
    int value_;
};

template<typename T>
class ConditionVariable {
public:
    ConditionVariable() { pthread_cond_init(&cond_, nullptr); }
    ~ConditionVariable() { pthread_cond_destroy(&cond_); }
    
    void wait(Mutex<T>& mutex) {
        pthread_cond_wait(&cond_, &mutex.mutex_);
    }
    
    void notify_one() { pthread_cond_signal(&cond_); }
    void notify_all() { pthread_cond_broadcast(&cond_); }
    
private:
    pthread_cond_t cond_;
};

template<typename JobType>
class ThreadPool {
public:
    ThreadPool(size_t numThreads) : stop_(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            threads_.emplace_back(&ThreadPool::worker, this);
        }
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }
    
    void enqueue(JobType job) {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            jobs_.push(std::move(job));
        }
        condition_.notify_one();
    }
    
private:
    std::vector<std::thread> threads_;
    std::queue<JobType> jobs_;
    std::mutex queueMutex_;
    ConditionVariable<ThreadPool> condition_;
    bool stop_;
    
    void worker() {
        while (true) {
            JobType job;
            {
                std::unique_lock<std::mutex> lock(queueMutex_);
                condition_.wait(queueMutex_);
                if (stop_ && jobs_.empty()) {
                    return;
                }
                job = std::move(jobs_.front());
                jobs_.pop();
            }
            job();
        }
    }
};

// Example job class
class PrintJob {
public:
    PrintJob(int x, int y) : x_(x), y_(y) {}
    
    void operator()() const {
        std::cout << "Processing (" << x_ << ", " << y_ << ")\n";
    }
    
private:
    int x_, y_;
};

int main() {
    ThreadPool<PrintJob> pool(4);
    
    for (int i = 0; i < 10; ++i) {
        pool.enqueue(PrintJob(i, i * 2));
    }
    
    // Pool will be destructed automatically, waiting for all jobs to finish.
    return 0;
}
