#ifndef RTOS_SIM_H
#define RTOS_SIM_H

#include <stdint.h>

#define QUEUE_SIZE 16

// Sensör verisi yapısı (örnek olarak sadece float değer)
typedef struct {
    float value;
} sensor_data_t;

/**
 * @brief Simülasyonu başlatır (producer & consumer thread'lerini oluşturur)
 */
void start_rtos_simulation(void);

#endif // RTOS_SIM_H
