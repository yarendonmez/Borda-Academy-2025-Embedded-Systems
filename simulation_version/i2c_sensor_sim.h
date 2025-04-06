#ifndef I2C_SENSOR_SIM_H
#define I2C_SENSOR_SIM_H

#include <stdint.h>

/**
 * @brief Kullanılacak sensör türlerini tanımlar.
 *        TEMP_SENSOR      -> Sıcaklık sensörü
 *        HUMIDITY_SENSOR  -> Nem sensörü
 *        CO2_SENSOR       -> Karbondioksit sensörü
 */
typedef enum {
    TEMP_SENSOR,
    HUMIDITY_SENSOR,
    CO2_SENSOR
} sensor_t;

/**
 * @brief Simüle edilmiş bir I2C sensör okuma fonksiyonu.
 * 
 * @param device_address  Sensörün I2C adresi (gerçek donanımda kullanılır ama burada sadece yer tutucu).
 * @param sensor_type     Okunmak istenen sensör tipi (sıcaklık, nem, CO2).
 * @return float          Simüle edilmiş ölçüm değeri.
 * 
 * @note Bu fonksiyon, gerçek sensör olmadığında test yapabilmek amacıyla
 *       rastgele ancak mantıklı aralıklarda değer üretir.
 */
float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type);

#endif // I2C_SENSOR_SIM_H
