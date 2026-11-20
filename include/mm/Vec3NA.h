#ifndef MM_VEC3NA_H
#define MM_VEC3NA_H

namespace mm {
// three floats without Vec3's 16-byte alignment (12 bytes; ptlib's KeyFrameIP writes x, y and z of one). Only
// the components are known.
struct Vec3NA {
    float x;
    float y;
    float z;

    static const Vec3NA zero;  // EmitterManager::getFreeParticle's (the symbol is the original's)
};
}  // namespace mm

#endif
