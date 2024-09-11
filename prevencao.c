#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Cria dois mutexes
pthread_mutex_t lock1, lock2;

// Processo A
void* processoA() {
    // Sempre adquire os locks na mesma ordem
    pthread_mutex_lock(&lock1);
    printf("Processo A pegou lock1\n");

    sleep(1); // Simula algum processamento

    pthread_mutex_lock(&lock2);
    printf("Processo A pegou lock2\n");

    // Liberar os dois mutexes
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("Processo A liberou lock1 e lock2 e está finalizado\n");

    return NULL;
}

// Processo B
void* processoB() {
    // Processo B também segue a mesma ordem de aquisição
    pthread_mutex_lock(&lock1); // Alterado para garantir a ordem
    printf("Processo B pegou lock1\n");

    sleep(1); // Simula algum processamento

    pthread_mutex_lock(&lock2);
    printf("Processo B pegou lock2\n");

    // Liberar os dois mutexes
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("Processo B liberou lock1 e lock2 e está finalizado\n");

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Inicia os dois mutexes
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Cria duas threads distintas
    pthread_create(&t1, NULL, processoA, NULL);
    pthread_create(&t2, NULL, processoB, NULL);

    // Espera as duas threads acabarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroi os dois mutexes
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("Programa finalizou.\n");

    return 0;
}
