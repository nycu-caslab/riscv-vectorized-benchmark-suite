#ifndef CONV_H
#define CONV_H

#include <stdlib.h>
#include <stdint.h>

void conv(const uint8_t* dst, const uint8_t* src, const uint8_t* wei, size_t m, size_t n);
void conv_scalar(const uint8_t* dst, const uint8_t* src, const uint8_t* wei, size_t m, size_t n);
void puint8_t(const uint8_t* src, size_t len);

#endif