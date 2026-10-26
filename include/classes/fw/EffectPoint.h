#ifndef CLASSES_FW_EFFECTPOINT_H
#define CLASSES_FW_EFFECTPOINT_H

#ifndef FW_EFFECT_POINT_PATH
#define FW_EFFECT_POINT_PATH "D:/Monolithsoft/BF2/prog/application/BF2\\framework/effect/effect_point.h"
#endif

#include "mm/MMStdBase.h"
#include "mm/Mat44.h"

namespace fw {
// table 0x7100B41648
class EffectPoint {
public:
    virtual ~EffectPoint();  // slot 0

    unsigned int getPointCount() const;
    // GfComEffectCaster::getEfpData returns the first and copies out the second for a point name (the names of the
    // parameters are not the original's)
    const char* getParentName(const char* name);
    mm::Mat44 getOffset(const char* name);
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
};
}  // namespace fw

#endif
