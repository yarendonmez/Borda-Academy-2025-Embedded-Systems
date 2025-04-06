#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <stdint.h>

float apply_median_filter(const float *buffer, uint8_t window_size);

#endif // MEDIAN_FILTER_H
