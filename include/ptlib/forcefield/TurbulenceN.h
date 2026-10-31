#ifndef PTLIB_FORCEFIELD_TURBULENCEN_H
#define PTLIB_FORCEFIELD_TURBULENCEN_H

#include "mm/Vec3.h"

namespace ptlib {

// Perlin's improved noise (particle_force_field.cpp); p is the permutation twice over
class ImprovedNoise {
public:
    ImprovedNoise();
    float noise(float x, float y, float z);

    int p[512];
};

// a turbulence made of ImprovedNoise octaves (particle_force_field.cpp)
class TurbulenceN {
public:
    static void init();
    static void updateTime(float time);
    static void turb3d(mm::Vec3& out, const mm::Vec3& pos, float frequency, float amplitude, int octaves);

    static float s_fTotalTime;
    static ImprovedNoise s_noise;
};

}  // namespace ptlib

#endif
