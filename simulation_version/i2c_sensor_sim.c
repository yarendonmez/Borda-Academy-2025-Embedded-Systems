#include <stdlib.h>          // rand() fonksiyonu için
#include "i2c_sensor_sim.h"  // Sensör tipi ve fonksiyon prototipi

/**
 * @brief Belirtilen sensör türüne göre sahte (mock) veri üretir.
 * 
 * @param device_address  Sensörün I2C adresi (gerçekte kullanılsa da simülasyonda etkisiz).
 * @param sensor_type     Üretilecek sensör verisinin tipi.
 * @return float          Sensör tipi için rastgele üretilmiş ölçüm değeri.
 */
float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type) {
    switch (sensor_type) {
        case TEMP_SENSOR:
            // 20.0°C - 40.0°C aralığında sıcaklık değeri
            return 20.0f + (rand() % 1000) / 50.0f;

        case HUMIDITY_SENSOR:
            // 30% - 100% bağıl nem aralığında değer
            return 30.0f + (rand() % 700) / 10.0f;

        case CO2_SENSOR:
            // 400 - 1400 ppm arası karbondioksit değeri
            return 400.0f + (rand() % 1001);

        default:
            // Geçersiz sensör tipi için varsayılan dönüş
            return 0.0f;
    }
}
