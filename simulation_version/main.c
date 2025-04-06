#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>             // sleep() için (Linux/macOS)
#include "i2c_sensor_sim.h"     // Sensör verisi üretimi
#include "median_filter.h"      // Medyan filtre fonksiyonu
#include "circular_buffer.h"    // Dairesel tampon (circular buffer)
#include "statistics.h"         // İstatistik hesaplama (min, max, medyan, std dev)

int main() {
    // Rastgele sayı üretimi başlatılıyor (farklı simülasyonlar için)
    srand(time(NULL));

    // Sensör adresleri (örnek I2C adresleri, sadece simülasyon için)
    uint8_t temp_sensor_address = 0x48;
    uint8_t humidity_sensor_address = 0x40;
    uint8_t co2_sensor_address = 0x61;

    // Her sensör için dairesel buffer başlatılıyor
    circular_buffer_t temp_buffer, humidity_buffer, co2_buffer;
    buffer_init(&temp_buffer);
    buffer_init(&humidity_buffer);
    buffer_init(&co2_buffer);

    printf("=== Sensör Simülasyon Başladı ===\n");

    // 20 ölçüm alınacak (1 Hz frekans ile)
    for (int i = 0; i < 20; i++) {
        // 1. Ham sensör verilerini oku (simülasyon)
        float temp_raw = i2c_sensor_read(temp_sensor_address, TEMP_SENSOR);
        float humidity_raw = i2c_sensor_read(humidity_sensor_address, HUMIDITY_SENSOR);
        float co2_raw = i2c_sensor_read(co2_sensor_address, CO2_SENSOR);

        // 2. Ham verileri filtrele (şu anlık 1 elemanlık pencere ile)
        float temp_filtered = apply_median_filter(&temp_raw, 1);
        float humidity_filtered = apply_median_filter(&humidity_raw, 1);
        float co2_filtered = apply_median_filter(&co2_raw, 1);

        // 3. Filtrelenmiş verileri buffer’a ekle
        buffer_push(&temp_buffer, temp_filtered);
        buffer_push(&humidity_buffer, humidity_filtered);
        buffer_push(&co2_buffer, co2_filtered);

        // 4. Ölçüm çıktısını yazdır
        printf("Ölçüm %02d:\n", i + 1);
        printf("  Sıcaklık: %.2f °C\n", temp_filtered);
        printf("  Nem     : %.2f %%\n", humidity_filtered);
        printf("  CO2     : %.2f ppm\n", co2_filtered);
        printf("----------------------------\n");

        // 1 saniye bekle (1 Hz örnekleme için)
        sleep(1);
    }

    // 5. Ölçüm tamamlandıktan sonra buffer'lardan verileri çek
    float temp_data[BUFFER_SIZE], humidity_data[BUFFER_SIZE], co2_data[BUFFER_SIZE];
    uint8_t temp_count = 0, humidity_count = 0, co2_count = 0;

    buffer_get_all(&temp_buffer, temp_data, &temp_count);
    buffer_get_all(&humidity_buffer, humidity_data, &humidity_count);
    buffer_get_all(&co2_buffer, co2_data, &co2_count);

    // 6. İstatistikleri hesapla
    stats_result_t temp_stats, humidity_stats, co2_stats;
    calculate_statistics(temp_data, temp_count, &temp_stats);
    calculate_statistics(humidity_data, humidity_count, &humidity_stats);
    calculate_statistics(co2_data, co2_count, &co2_stats);

    // 7. BLE paketi simülasyonu olarak istatistikleri yazdır
    printf("\n=== BLE Paketi Simülasyonu ===\n");
    printf("Sıcaklık -> Min: %.2f  Max: %.2f  Medyan: %.2f  StdDev: %.2f\n",
        temp_stats.min, temp_stats.max, temp_stats.median, temp_stats.std_dev);
    printf("Nem      -> Min: %.2f  Max: %.2f  Medyan: %.2f  StdDev: %.2f\n",
        humidity_stats.min, humidity_stats.max, humidity_stats.median, humidity_stats.std_dev);
    printf("CO2      -> Min: %.2f  Max: %.2f  Medyan: %.2f  StdDev: %.2f\n",
        co2_stats.min, co2_stats.max, co2_stats.median, co2_stats.std_dev);

    printf("=== Simülasyon Bitti ===\n");

    return 0;
}
