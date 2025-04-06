#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 32  // İstediğin kadar değiştirebilirsin

typedef struct {
    float data[BUFFER_SIZE];   // Verileri tutan dizi
    uint8_t head;              // Son eklenen verinin indeksini gösterir
    uint8_t count;             // Kaç veri var şu anda?
} circular_buffer_t;

/**
 * @brief Buffer'ı başlatır.
 */
void buffer_init(circular_buffer_t *buffer);

/**
 * @brief Buffer'a yeni veri ekler.
 *        Eğer buffer doluysa en eski veri silinir.
 */
void buffer_push(circular_buffer_t *buffer, float value);

/**
 * @brief Buffer içindeki tüm değerleri hedef diziye kopyalar.
 * 
 * @param buffer       Kaynak buffer
 * @param out_array    Hedef dizi
 * @param out_count    Kopyalanan veri sayısı (çıkış)
 */
void buffer_get_all(circular_buffer_t *buffer, float *out_array, uint8_t *out_count);

#endif // CIRCULAR_BUFFER_H
