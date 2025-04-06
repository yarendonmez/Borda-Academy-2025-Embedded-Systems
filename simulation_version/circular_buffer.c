#include "circular_buffer.h"

void buffer_init(circular_buffer_t *buffer) {
    buffer->head = 0;
    buffer->count = 0;
}

void buffer_push(circular_buffer_t *buffer, float value) {
    buffer->data[buffer->head] = value;

    // Kafa ileri alınır (modulo ile sarılır)
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;

    // Dolu değilse sayacı artır, doluysa üzerine yaz
    if (buffer->count < BUFFER_SIZE) {
        buffer->count++;
    }
}

void buffer_get_all(circular_buffer_t *buffer, float *out_array, uint8_t *out_count) {
    *out_count = buffer->count;
    uint8_t start = (buffer->head + BUFFER_SIZE - buffer->count) % BUFFER_SIZE;

    for (uint8_t i = 0; i < buffer->count; i++) {
        out_array[i] = buffer->data[(start + i) % BUFFER_SIZE];
    }
}
