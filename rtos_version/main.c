#include <stdio.h>              // printf için
#include <stdlib.h>             // srand, rand
#include <time.h>               // time()
#include "rtos_sim.h"           // RTOS simülasyon başlatıcı

/**
 * Ana fonksiyon, RTOS simülasyonunu başlatır.
 * Producer thread sensör verisi üretir,
 * Consumer thread veriyi tüketir.
 */
int main() {
    // Rastgele veri üretimi için başlangıç seed’i (her çalışmada farklı veri)
    srand(time(NULL));

    // RTOS benzeri thread'li simülasyonu başlat
    printf("=== RTOS Producer-Consumer Simülasyonu Başlatılıyor ===\n");
    start_rtos_simulation();

    // Buraya normalde dönmez çünkü thread'ler sonsuz döngüde
    return 0;
}
