#ifndef CLASSES_ML_IDRDRAWWORKINFO_H
#define CLASSES_ML_IDRDRAWWORKINFO_H
#include "mm/Vec3.h"

namespace ml {
// what ml's draw system hands each IDrDrawCallback stage; only what the code reads is named
class IDrDrawWorkInfo {
public:
    unsigned char pad_0[0xB0];
    // layer::LayerObjManager::apply hands it to LayerSortMan::begin, which sorts the 3D objects by their distance to
    // it (the name is not the original's)
    mm::Vec3 m_eyePos;  // 0xB0
    unsigned char pad_C0[0x4A0];
    // layer::LayerManager's apply and finalRender draw only when it is 0 (the name is not the original's)
    int m_subPass;
};
}  // namespace ml

#endif
