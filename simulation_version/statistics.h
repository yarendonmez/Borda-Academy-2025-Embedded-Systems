#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdint.h>

// Hesaplanan istatistik sonuçlarını tutacak yapı
typedef struct {
    float min;
    float max;
    float median;
    float std_dev;
} stats_result_t;

/**
 * @brief Verilen float dizisi için istatistiksel hesaplamalar yapar.
 * 
 * @param data        Giriş verileri
 * @param count       Veri sayısı
 * @param result_out  Sonuç yapısı
 */
void calculate_statistics(const float *data, uint8_t count, stats_result_t *result_out);

#endif // STATISTICS_H
