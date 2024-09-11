// Criação do deadlock
// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// // Cria dois mutexes
// pthread_mutex_t lock1, lock2;

// // Processo A
// void* processoA() {
//   pthread_mutex_lock(&lock1);
//   printf("Processo A pegou lock1\n");

//   sleep(1); // Simula algum processamento

//   pthread_mutex_lock(&lock2);
//   printf("Processo A pegou lock2\n");

//     // Liberar os dois mutexes
//   pthread_mutex_unlock(&lock2);
//   pthread_mutex_unlock(&lock1);
// }

// // Processo B
// void* processoB() {
//   pthread_mutex_lock(&lock2);
//   printf("Processo B pegou lock2\n");

//   sleep(1); // Simula algum processamento

//   pthread_mutex_lock(&lock1);
//   printf("Processo B pegou lock1\n");

//     // Liberar os dois mutexes
//   pthread_mutex_unlock(&lock1);
//   pthread_mutex_unlock(&lock2);
// }

// int main() {
//   pthread_t t1, t2;

//   // Inicia os dois mutexes
//   pthread_mutex_init(&lock1, NULL);
//   pthread_mutex_init(&lock2, NULL);

//     // Cria duas threads distintas
//   pthread_create(&t1, NULL, processoA, NULL);
//   pthread_create(&t2, NULL, processoB, NULL);

//     // Espera as duas threads acabarem
//   pthread_join(t1, NULL);
//   pthread_join(t2, NULL);

//     // Destroi os dois mutexes
//   pthread_mutex_destroy(&lock1);
//   pthread_mutex_destroy(&lock2);

//   printf("Programa finalizou.");

//   return 0;
// }

// Detecção do deadlock
// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <time.h>

// // Cria dois mutexes
// pthread_mutex_t lock1, lock2;

// // Função para verificar se há deadlock
// void detect_deadlock() {
//     int deadlock_detected = 0;
//     time_t start_time, end_time;

//     // Obtém o tempo de início
//     time(&start_time);

//     sleep(3); // Tempo para esperar e ver se há deadlock (ajuste conforme necessário)

//     if (pthread_mutex_trylock(&lock1) != 0 && pthread_mutex_trylock(&lock2) != 0) {
//         deadlock_detected = 1;
//     }

//     // Obtém o tempo de fim
//     time(&end_time);

//     // Calcula o tempo em segundos para detectar o deadlock
//     double time_taken = difftime(end_time, start_time);

//     if (deadlock_detected) {
//         printf("Deadlock detectado! Tempo para detectar: %.2f segundos\n", time_taken);
//     } else {
//         // Libera os mutexes se não houver deadlock
//         if (pthread_mutex_trylock(&lock1) == 0) pthread_mutex_unlock(&lock1);
//         if (pthread_mutex_trylock(&lock2) == 0) pthread_mutex_unlock(&lock2);
//     }
// }

// // Processo A
// void* processoA() {
//     pthread_mutex_lock(&lock1);
//     printf("Processo A pegou lock1\n");

//     sleep(1); // Simula algum processamento

//     pthread_mutex_lock(&lock2);
//     printf("Processo A pegou lock2\n");

//     // Liberar os dois mutexes
//     pthread_mutex_unlock(&lock2);
//     pthread_mutex_unlock(&lock1);
//     return NULL;
// }

// // Processo B
// void* processoB() {
//     pthread_mutex_lock(&lock2);
//     printf("Processo B pegou lock2\n");

//     sleep(1); // Simula algum processamento

//     pthread_mutex_lock(&lock1);
//     printf("Processo B pegou lock1\n");

//     // Liberar os dois mutexes
//     pthread_mutex_unlock(&lock1);
//     pthread_mutex_unlock(&lock2);
//     return NULL;
// }

// int main() {
//     pthread_t t1, t2, t3;

//     // Inicia os dois mutexes
//     pthread_mutex_init(&lock1, NULL);
//     pthread_mutex_init(&lock2, NULL);

//     // Cria duas threads distintas para os processos
//     pthread_create(&t1, NULL, processoA, NULL);
//     pthread_create(&t2, NULL, processoB, NULL);

//     // Cria uma thread para detecção de deadlock
//     pthread_create(&t3, NULL, (void*)detect_deadlock, NULL);

//     // Espera as duas threads acabarem
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     // Espera a thread de detecção de deadlock
//     pthread_join(t3, NULL);

//     // Destroi os dois mutexes
//     pthread_mutex_destroy(&lock1);
//     pthread_mutex_destroy(&lock2);

//     printf("Programa finalizou.\n");

//     return 0;
// }

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Cria dois mutexes
pthread_mutex_t lock1, lock2;

// Função para verificar se há deadlock e resolvê-lo
void detect_and_resolve_deadlock() {
    int deadlock_detected = 0;
    time_t start_time, end_time;

    // Obtém o tempo de início
    time(&start_time);

    sleep(3); // Tempo para esperar e ver se há deadlock (ajuste conforme necessário)

    // Tenta pegar ambos os locks
    if (pthread_mutex_trylock(&lock1) != 0 && pthread_mutex_trylock(&lock2) != 0) {
        deadlock_detected = 1;
    }

    // Obtém o tempo de fim
    time(&end_time);

    // Calcula o tempo em segundos para detectar o deadlock
    double time_taken = difftime(end_time, start_time);

    if (deadlock_detected) {
        printf("Deadlock detectado! Tempo para detectar: %.2f segundos\n", time_taken);

        // Resolução forçada: libera os locks manualmente
        pthread_mutex_unlock(&lock1);
        pthread_mutex_unlock(&lock2);
        printf("Deadlock resolvido forçadamente! Locks liberados.\n");
    } else {
        // Libera os mutexes se não houver deadlock
        if (pthread_mutex_trylock(&lock1) == 0) pthread_mutex_unlock(&lock1);
        if (pthread_mutex_trylock(&lock2) == 0) pthread_mutex_unlock(&lock2);
    }
}

// Processo A
void* processoA() {
    pthread_mutex_lock(&lock1);
    printf("Processo A pegou lock1\n");

    sleep(1); // Simula algum processamento

    pthread_mutex_lock(&lock2);
    printf("Processo A pegou lock2\n");

    // Liberar os dois mutexes
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

// Processo B
void* processoB() {
    pthread_mutex_lock(&lock2);
    printf("Processo B pegou lock2\n");

    sleep(1); // Simula algum processamento

    pthread_mutex_lock(&lock1);
    printf("Processo B pegou lock1\n");

    // Liberar os dois mutexes
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Inicia os dois mutexes
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Cria duas threads distintas para os processos
    pthread_create(&t1, NULL, processoA, NULL);
    pthread_create(&t2, NULL, processoB, NULL);

    // Cria uma thread para detecção e resolução de deadlock
    pthread_create(&t3, NULL, (void*)detect_and_resolve_deadlock, NULL);

    // Espera as duas threads acabarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Espera a thread de detecção de deadlock
    pthread_join(t3, NULL);

    // Destroi os dois mutexes
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("Programa finalizou.\n");

    return 0;
}
