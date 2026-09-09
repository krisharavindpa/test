#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t t[5];
pthread_t a[5];

void* weld(void* arg) {
    long id = (long)arg;
    int first = id, second = (id + 1) % 5;

    // Last arm reverses pickup order to prevent circular deadlock
    if (id == 4) { int tmp = first; first = second; second = tmp; }

    printf("Arm %ld is idle.\n", id);
    sleep(1);

    pthread_mutex_lock(&t[first]);
    pthread_mutex_lock(&t[second]);

    printf("--> Arm %ld is WELDING.\n", id);
    sleep(1);

    pthread_mutex_unlock(&t[first]);
    pthread_mutex_unlock(&t[second]);

    printf("Arm %ld finished welding.\n", id);
    return NULL;
}

int main() {
    for (long i = 0; i < 5; i++) {
        pthread_mutex_init(&t[i], NULL);
        pthread_create(&a[i], NULL, weld, (void*)i);
    }
    for (int i = 0; i < 5; i++) pthread_join(a[i], NULL);
    return 0;
}
