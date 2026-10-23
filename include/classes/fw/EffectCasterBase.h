#ifndef CLASSES_FW_EFFECTCASTERBASE_H
#define CLASSES_FW_EFFECTCASTERBASE_H

#include "mm/mtl/FixedVector.h"

namespace fw { class EffectPoint; }
namespace mm { class Mat44; }

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41320
class EffectCasterBase {
public:
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 0
    virtual void postUpdate(fw::UpdateInfo const&) = 0;  // slot 1
    virtual ~EffectCasterBase();  // slot 2

    void setScl(float scl);
    void setMotionFrame(float frame);
    void setStateName(const char* name);
    void setEfpMat(mm::Mat44& mtx, const char* name, int index);
    // moves the caster to layer through EffectManager, with its point (the names of the parameters are not the
    // original's)
    void changeLayer(unsigned int index, unsigned int layer);

    unsigned char pad_8[0x8];
    EffectPoint* m_pPoint;  // the constructor's, counted (the name is not the original's)
    unsigned char pad_18[0x24];
    unsigned int m_layer;  // the constructor's, changeLayer's (the name is not the original's)
    unsigned char pad_40[0x10];

    // every caster (the file's static initializer constructs it, tail walks it)
    static mm::mtl::FixedVector<EffectCasterBase*, 256> s_casterList;
};
}  // namespace fw

#endif
