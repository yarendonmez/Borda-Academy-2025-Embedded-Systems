#include "statistics.h"
#include <stdlib.h>
#include <math.h>   // sqrt()
#include <string.h> // memcpy()

// qsort için karşılaştırma fonksiyonu
int compare_float(const void *a, const void *b) {
    float fa = *(float*)a;
    float fb = *(float*)b;
    return (fa > fb) - (fa < fb);
}

void calculate_statistics(const float *data, uint8_t count, stats_result_t *result_out) {
    if (count == 0) return;

    // Min & Max
    float min = data[0];
    float max = data[0];
    float sum = 0.0;

    for (uint8_t i = 0; i < count; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
        sum += data[i];
    }

    float mean = sum / count;

    // Std. Sapma
    float variance = 0.0;
    for (uint8_t i = 0; i < count; i++) {
        float diff = data[i] - mean;
        variance += diff * diff;
    }
    float std_dev = sqrt(variance / count);

    // Medyan
    float sorted[count];
    memcpy(sorted, data, count * sizeof(float));
    qsort(sorted, count, sizeof(float), compare_float);
    float median;
    if (count % 2 == 0) {
        median = (sorted[count/2 - 1] + sorted[count/2]) / 2.0f;
    } else {
        median = sorted[count/2];
    }

    // Sonuçları doldur
    result_out->min = min;
    result_out->max = max;
    result_out->median = median;
    result_out->std_dev = std_dev;
}
