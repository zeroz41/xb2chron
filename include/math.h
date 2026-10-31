#ifndef MATH_H
#define MATH_H

// The C library's math functions, as the module imports them from NintendoSDK.

#ifdef __cplusplus
extern "C" {
#endif

float sqrtf(float x);
double sqrt(double x);
float sinf(float x);
float cosf(float x);
float acosf(float x);
float asinf(float x);
float atan2f(float y, float x);
float tanf(float x);
float fabsf(float x);
float fmaxf(float x, float y);
float floorf(float x);
float fmodf(float x, float y);
float modff(float x, float* integral);
float ceilf(float x);
float log2f(float x);
float logf(float x);
float powf(float x, float y);

#ifdef __cplusplus
}

// the C++ library's overload for a float (an assertion in WindBlender::changeNode cites `abs(time)`)
inline float abs(float x) {
    return ::fabsf(x);
}
#endif

#endif
