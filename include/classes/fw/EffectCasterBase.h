#ifndef CLASSES_FW_EFFECTCASTERBASE_H
#define CLASSES_FW_EFFECTCASTERBASE_H

#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/mm/mtl/ReferenceObject.h"

namespace fw { class EffectPoint; }
namespace mm { class Mat44; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41320
class EffectCasterBase {
public:
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 0
    virtual void postUpdate(fw::UpdateInfo const&) = 0;  // slot 1
    virtual ~EffectCasterBase();  // slot 2

    // registers the caster with EffectManager (when there is one) and in s_casterList
    EffectCasterBase(const EffectPoint* point, unsigned int layer);
    // deletes every caster whose m_isDead is set (EffectManager::tail calls it)
    static void tail();

    void setScl(float scl);
    void setMotionFrame(float frame);
    void setStateName(const char* name);
    void setEfpMat(mm::Mat44& mtx, const char* name, int index);
    // moves the caster to layer through EffectManager, with its point (the names of the parameters are not the
    // original's)
    void changeLayer(unsigned int index, unsigned int layer);

    // cleared by the constructor, released by the destructor (reference_object.h's `m_RefCount > 0`); what it
    // holds is unknown
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> pad_8;
    EffectPoint* m_pPoint;  // the constructor's, counted (the name is not the original's)
    void* pad_18;  // the constructor clears 0x18..0x2C
    void* pad_20;
    unsigned int pad_28;
    unsigned char pad_2c[0x4];
    // Framework::getAllocator()'s, EffectCasterSend::create's allocator (the name is not the original's)
    mm::mtl::IAllocator* m_pAllocator;
    // 1 + the point's getPointCount(), EffectCasterSend::create's count (the name is not the original's)
    unsigned int m_pointCount;
    unsigned int m_layer;  // the constructor's, changeLayer's (the name is not the original's)
    bool m_isDead;  // tail deletes the casters that have it set (the name is not the original's)
    unsigned char pad_41[0xF];

    // every caster (the file's static initializer constructs it, tail walks it)
    static mm::mtl::FixedVector<EffectCasterBase*, 256> s_casterList;
};
}  // namespace fw

#endif
