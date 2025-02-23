#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SEM_KEY IPC_PRIVATE

int main() {
    int semid;
    struct sembuf sb = {0, -1, 0};

    // 创建信号量
    if ((semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(1);
    }

    // 初始化信号量
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // 子进程
        printf("Child process\n");

        // 等待信号量
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }

        printf("Child process finished\n");
    } else {
        // 父进程
        printf("Parent process\n");

        // 等待信号量
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }

        printf("Parent process finished\n");

        // 删除信号量
        if (semctl(semid, 0, IPC_RMID) == -1) {
            perror("semctl");
            exit(1);
        }
    }

    return 0;
}