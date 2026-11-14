#ifndef CLASSES_ML_IDRDRAWWORKINFO_H
#define CLASSES_ML_IDRDRAWWORKINFO_H
#include "mm/Vec3.h"
#include "mm/Mat44.h"

namespace ml {
// what ml's draw system hands each IDrDrawCallback stage; only what the code reads is named
class IDrDrawWorkInfo {
public:
    unsigned char pad_0[0xB0];
    // layer::LayerObjManager::apply hands it to LayerSortMan::begin, which sorts the 3D objects by their distance to
    // it (the name is not the original's)
    mm::Vec3 m_eyePos;  // 0xB0
    unsigned char pad_C0[0x114];
    // 24 floats cloud::CloudObjReduction::update sends to its shader (6 x 4: the name and the reading as planes are
    // not the original's)
    float m_planes[24];  // 0x1D4
    unsigned char pad_234[0x1EC];
    // three matrices cloud::CloudObjFlow::update sends after its own (names not the original's)
    mm::Mat44 m_flowMat[3];  // 0x420
    float m_flowVec[3];      // 0x4E0, cloud::CloudObjFlow::update's second uniform
    unsigned char pad_4EC[0x74];
    // layer::LayerManager's apply and finalRender draw only when it is 0 (the name is not the original's)
    int m_subPass;  // DrMan::applyView stores the view index
    unsigned char pad_564[0x4];
    bool m_viewFlag;  // 0x568: DrMan::applyView copies DrMan::m_viewFlag here (the name is not the original's)
    unsigned char pad_569[0x17];  // sizeof 0x580: DrMan keeps one per view at 0x660
};
}  // namespace ml

#endif
