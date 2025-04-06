#include <stdlib.h>   // malloc, free, qsort
#include <string.h>   // memcpy

/**
 * @brief float dizisi için karşılaştırma fonksiyonu (qsort ile kullanılacak).
 */
int compare_floats(const void *a, const void *b) {
    float fa = *(const float *)a;
    float fb = *(const float *)b;
    return (fa > fb) - (fa < fb); // klasik üçlü dönüş
}

/**
 * @brief Hareketli medyan filtre uygular.
 * 
 * @param buffer      Giriş verilerini içeren float dizisi
 * @param window_size Kaç elemanlık pencere kullanılacağı
 * @return float      Medyan değer
 */
float apply_median_filter(const float *buffer, uint8_t window_size) {
    if (window_size == 0) return 0.0;

    // Veriyi değiştirmemek için kopyasını alıyoruz
    float *temp = (float *)malloc(window_size * sizeof(float));
    if (!temp) return 0.0; // Bellek hatası

    memcpy(temp, buffer, window_size * sizeof(float)); // orijinal veriyi koru

    qsort(temp, window_size, sizeof(float), compare_floats); // sıralama işlemi

    float median;
    if (window_size % 2 == 0) {
        // Çift pencere boyutunda ortadaki iki değerin ortalaması alınır
        median = (temp[window_size/2 - 1] + temp[window_size/2]) / 2.0f;
    } else {
        // Tek pencere boyutunda ortadaki eleman
        median = temp[window_size/2];
    }

    free(temp); // geçici diziyi temizle
    return median;
}
