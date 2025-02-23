#include <pthread.h>
#include <iostream>
#include <list>
#include <semaphore.h>

#define MAX_QUEUE_SIZE 10 // 定义作业队列的最大容量

struct Job {
    Job(int x = 0, int y = 0) : x(x), y(y) {}
    int x, y;
};

std::list<Job*> job_queue;
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count; // 表示队列中作业的数量
sem_t job_queue_space; // 表示队列中的空位数量

void ProcessJob(Job* job) {
    std::cout << "Thread " << (int)pthread_self();
    std::cout << " processing (" << job->x << ", " << job->y << ")\n";
}

void* DequeueJob(void* arg) {
    while (true) {
        Job* job = nullptr;
        sem_wait(&job_queue_count); // 等待队列中有新作业

        pthread_mutex_lock(&job_queue_mutex);
        if (!job_queue.empty()) {
            job = job_queue.front();
            job_queue.pop_front();
            sem_post(&job_queue_space); // 增加空位
        }
        pthread_mutex_unlock(&job_queue_mutex);

        if (!job) break; // 如果没有作业则退出
        ProcessJob(job);
        delete job;
    }
    return nullptr;
}

void* EnqueueJob(void* arg) {
    Job* job = reinterpret_cast<Job*>(arg);
    sem_wait(&job_queue_space); // 等待队列有空位

    pthread_mutex_lock(&job_queue_mutex);
    job_queue.push_back(job);
    sem_post(&job_queue_count); // 增加作业数量
    std::cout << "Thread " << (int)pthread_self();
    std::cout << " enqueueing (" << job->x << ", " << job->y << ")\n";
    pthread_mutex_unlock(&job_queue_mutex);

    return nullptr;
}

int main() {
    int i;
    pthread_t threads[8];
    
    // 初始化信号量
    sem_init(&job_queue_count, 0, 0); // 初始值为0，表示开始时队列中没有作业
    sem_init(&job_queue_space, 0, MAX_QUEUE_SIZE); // 初始值为队列最大容量

    // 创建生产者线程
    for (i = 0; i < 5; ++i) {
        Job* p = new Job(i + 1, (i + 1) * 2);
        pthread_create(&threads[i], NULL, EnqueueJob, p);
    }

    // 创建消费者线程
    for (i = 5; i < 8; ++i) {
        pthread_create(&threads[i], NULL, DequeueJob, nullptr);
    }

    // 等待线程终止
    for (i = 0; i < 8; ++i) {
        pthread_join(threads[i], NULL);
    }

    // 销毁信号量
    sem_destroy(&job_queue_count);
    sem_destroy(&job_queue_space);

    return 0;
}
