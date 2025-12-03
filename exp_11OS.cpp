#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc1(LPVOID lpParam) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 1: i = %d\n", i);
        Sleep(10);  // small sleep to better show interleaving
    }
    return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID lpParam) {
    for (int j = 1; j <= 5; j++) {
        printf("Thread 2: j = %d\n", j);
        Sleep(10);
    }
    return 0;
}

int main() {
    HANDLE hThread1, hThread2;
    DWORD dwThreadId1, dwThreadId2;

    printf("Main: creating threads\n");

    hThread1 = CreateThread(
        NULL,       // default security
        0,          // default stack size
        ThreadFunc1,// thread function
        NULL,       // parameter to thread function
        0,          // default creation flags
        &dwThreadId1
    );

    if (hThread1 == NULL) {
        fprintf(stderr, "Error: unable to create thread 1\n");
        return 1;
    }

    hThread2 = CreateThread(
        NULL,
        0,
        ThreadFunc2,
        NULL,
        0,
        &dwThreadId2
    );

    if (hThread2 == NULL) {
        fprintf(stderr, "Error: unable to create thread 2\n");
        return 1;
    }

    // Wait for both threads to finish
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    printf("Main: all threads completed\n");
    return 0;
}
