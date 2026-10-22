#ifndef MATH_H
#define MATH_H

// The C library's math functions, as the module imports them from NintendoSDK.

#ifdef __cplusplus
extern "C" {
#endif

float sqrtf(float x);
float sinf(float x);
float cosf(float x);
float acosf(float x);
float asinf(float x);
float atan2f(float y, float x);
float fabsf(float x);

#ifdef __cplusplus
}
#endif

#endif
