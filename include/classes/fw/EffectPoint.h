#ifndef CLASSES_FW_EFFECTPOINT_H
#define CLASSES_FW_EFFECTPOINT_H

#ifndef FW_EFFECT_POINT_PATH
#define FW_EFFECT_POINT_PATH "D:/Monolithsoft/BF2/prog/application/BF2\\framework/effect/effect_point.h"
#endif

#include "mm/MMStdBase.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/ReferenceFrame.h"

namespace fw { class UpdateInfo; }
namespace fw { class ModelObject; }

namespace fw {
// what an effect point list is built from (GfComEffectCaster::setupEfp fills one; the constructor reads these fields;
// the names are not the original's)
struct EfpInitData {
    // GfComEffectCaster::setupEfp's (inline: its zeroing stores are in setupEfp)
    EfpInitData() : size(0), data(nullptr), allocator(nullptr), model(nullptr) {}
    unsigned int pad_0;  // GfComEffectCaster::setupEfp copies its SetupInfo's 0x10 in; what it holds is unknown
    float scale;              // 0x4 multiplies each point's position unless 1
    unsigned int size;        // 0x8 the csvb's size (CCsvbData::Load's third argument)
    const void* data;         // 0x10 the csvb of the points, none when null
    mm::mtl::IAllocator* allocator;  // 0x18 CCsvbData::Load's
    ModelObject* model;       // 0x20 whose bones the parents name
    // 0x28 the frame of a parent by name (the constructor calls it per point)
    mm::mtl::Delegate<mm::mtl::IntrusivePtr<ReferenceFrame>(const char*)> createFrame;
    // 0x48 hands a parent's frame back by name (the destructor calls it per point)
    mm::mtl::Delegate<void(const char*)> releaseFrame;
};

// table 0x7100B41648
class EffectPoint {
public:
    // one row of the csvb: name, parent, position (scaled), rotation in degrees (the field names are not the
    // original's)
    struct Param {
        mm::Mat44 offset;                                // 0x00 getOffset's
        mm::Vec3 scale;                                  // 0x40 getScale's (the constructor sets zero)
        mm::mtl::IntrusivePtr<ReferenceFrame> frame;     // 0x50 the parent's frame (calcPoint syncs it)
        mm::mtl::FixStr<32> name;                        // 0x58 getPointName's
        unsigned int hash;                               // 0x7C mm::mtl::hashStrCrc of the name (getPointIndex)
        mm::mtl::FixStr<32> parentName;                  // 0x80 getParentName's
        int boneIndex;                                   // 0xA4 the parent's bone in the model, -1 without one
        bool dirty;                                      // 0xA8 setDirty/isDirty's; update recomputes a dirty one
    };

    EffectPoint(const EfpInitData& init);
    virtual ~EffectPoint();  // slot 0

    // signed: EffectManager::updateLayer compares it with cmp #1/b.lt
    int getPointCount() const;
    void update(const fw::UpdateInfo& info);
    // EffectManager::updateLayer marks each of a caster's points (the names of the parameters are not the original's)
    void setDirty(unsigned int index, bool dirty);
    // GfComEffectCaster::getEfpData returns the first and copies out the second for a point name (the names of the
    // parameters are not the original's)
    const char* getParentName(const char* name);
    mm::Mat44 getOffset(const char* name);
    int getPointIndex(const char* name) const;  // -1 when it has no point of that name
    const mm::Mat44& getPointTransform(int index) const;
    const char* getPointName(int index) const;
    const mm::Vec3& getScale(int index) const;
    bool isDirty(unsigned int index);
    void calcPoint(Param& param, mm::Mat44& mtx) const;
    void addRef() { ++m_RefCount; }
    // effect_point.h asserts `m_RefCount >= 0` before it drops one (EffectCasterBase's destructor)
    void release() {
#line 102 FW_EFFECT_POINT_PATH
        MM_ASSERT(m_RefCount >= 0);
        if (--m_RefCount == 0) {
            delete this;
        }
    }

    int m_RefCount;  // effect_point.h's assertion names it
    // EffectCasterBase::changeLayer sets it to the caster's new layer (the name is not the original's)
    unsigned int m_layer;
    mm::mtl::Vector<Param> m_params;           // 0x10 the csvb's rows
    mm::mtl::Vector<mm::Mat44> m_transforms;   // 0x38 one per point (getPointTransform's)
    ModelObject* m_model;                      // 0x60 EfpInitData's
    mm::mtl::Delegate<mm::mtl::IntrusivePtr<ReferenceFrame>(const char*)> m_createFrame;  // 0x68 EfpInitData's
    mm::mtl::Delegate<void(const char*)> m_releaseFrame;                                  // 0x88 EfpInitData's
};
}  // namespace fw

#endif
