#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t torches[N];
pthread_t arms[N];

void* weld(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    // Thinking / Idle
    printf("Arm %d is idle.\n", id);
    sleep(1);

    // Asymmetric pickup: Arm 4 picks up right first to break circular wait
    if (id == N - 1) {
        pthread_mutex_lock(&torches[right]);
        pthread_mutex_lock(&torches[left]);
    } else {
        pthread_mutex_lock(&torches[left]);
        pthread_mutex_lock(&torches[right]);
    }

    // Critical Section: Welding
    printf("--> Arm %d acquired torches %d and %d: WELDING.\n", id, left, right);
    sleep(2);

    // Release torches
    pthread_mutex_unlock(&torches[left]);
    pthread_mutex_unlock(&torches[right]);
    printf("Arm %d finished welding and released torches.\n", id);

    return NULL;
}

int main() {
    int ids[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&torches[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&arms[i], NULL, weld, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(arms[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&torches[i]);

    return 0;
}
