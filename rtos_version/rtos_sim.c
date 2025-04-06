#include "rtos_sim.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // sleep()

// Circular queue (basit veri yapısı)
sensor_data_t queue[QUEUE_SIZE];
int head = 0, tail = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;

// Thread fonksiyonları
void* producer_thread(void* arg) {
    while (1) {
        float generated_value = (rand() % 1000) / 10.0f; // Rastgele sensör verisi

        pthread_mutex_lock(&mutex);

        if (count == QUEUE_SIZE) {
            // Kuyruk doluysa veri alınmayacak, discard edilecek
            printf("[PRODUCER] ❌ VERİ KAYBEDİLDİ! Değer: %.2f | Kuyruk DOLU\n", generated_value);
        } else {
            // Kuyruğa veriyi ekle
            queue[tail].value = generated_value;
            tail = (tail + 1) % QUEUE_SIZE;
            count++;

            printf("[PRODUCER] ✅ Üretildi: %.2f | Kuyrukta: %d\n", generated_value, count);

            pthread_cond_signal(&cond_not_empty); // Consumer’a haber ver
        }

        pthread_mutex_unlock(&mutex);
        sleep(1); // 1 saniyede bir veri üret
    }
    return NULL;
}

void* consumer_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Kuyruk boşsa bekle
        while (count == 0) {
            pthread_cond_wait(&cond_not_empty, &mutex);
        }

        // Kuyruktan veri al
        float value = queue[head].value;
        head = (head + 1) % QUEUE_SIZE;
        count--;

        printf("    [CONSUMER] Tüketti: %.2f | Kuyrukta: %d\n", value, count);

        pthread_cond_signal(&cond_not_full); // Producer’a haber ver
        pthread_mutex_unlock(&mutex);

        // İşlem süresi uzunmuş gibi bekleyelim (consumer yavaş!)
        sleep(2);
    }
    return NULL;
}

void start_rtos_simulation(void) {
    pthread_t producer, consumer;

    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
}
