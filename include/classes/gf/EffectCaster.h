#ifndef CLASSES_GF_EFFECTCASTER_H
#define CLASSES_GF_EFFECTCASTER_H

#include "classes/fw/EffectCasterBase.h"
#include "mm/Mat44.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComEffectCaster; }

namespace gf {
// table 0x7100B65AF8
class EffectCaster : public ::fw::EffectCasterBase {
public:
    // GfComEffectCaster::setupCaster's (inline: its stores are in setupCaster)
    EffectCaster(const fw::EffectPoint* point, unsigned int layer)
        : EffectCasterBase(point, layer), m_pOwner(nullptr), m_isLeader(false) {
        m_mtx = mm::Mat44::identity;
        pad_44 = 0;
        pad_48 = 0;
        pad_4c = 0;
        pad_50 = 0;
    }
    virtual void update(fw::UpdateInfo const&);  // slot 0
    virtual void postUpdate(fw::UpdateInfo const&);  // slot 1
    // slot 2 holds EffectCasterBase's destructor: inline, nothing to destroy
    virtual ~EffectCaster() {}

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in EffectCaster's
    // code (between EffectCaster::update and GfComEffectCaster's getRTTI) and GfComEffectCaster::fn_71004B3B68 calls
    // it on its caster. What it does: copies the matrix to 0x60 (asserting its alignment), then walks the effect
    // point's transforms (getPointCount/getPointName/getPointTransform, "root"), setEfpMat for each and setDirty.
    void fn_71004B3B78(const mm::Mat44& mtx);

    unsigned int pad_44;  // zeroed by the constructor
    unsigned int pad_48;
    unsigned int pad_4c;
    unsigned int pad_50;
    unsigned char pad_54[0x4];
    GfComEffectCaster* m_pOwner;  // setupCaster's component (the name is not the original's)
    mm::Mat44 m_mtx;  // identity at construction, fn_71004B3B78 copies its matrix in (the name is not the original's)
    // set for the party leader's first caster (setupCaster; the name is not the original's)
    bool m_isLeader;
    unsigned char pad_a1[0xF];
};
}  // namespace gf

#endif
