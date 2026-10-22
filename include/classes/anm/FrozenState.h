#ifndef CLASSES_ANM_FROZENSTATE_H
#define CLASSES_ANM_FROZENSTATE_H

#include "anm/AsmBlender.h"

namespace anm { class AsmListener; }
namespace anm { struct ResStateData; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B813F8; a state holding its first clip still: entered at the clip's start, at no speed, it never
// updates
class FrozenState : public ::anm::AsmState {
public:
    FrozenState(const ResStateData* pRes, mm::mtl::IAllocator& allocator);
    virtual ~FrozenState();  // slot 0
    virtual void attach(AsmBlender* blender);  // slot 2
    virtual void dettach(AsmBlender* blender);  // slot 3
    virtual void onEnter(AsmListener* listener);  // slot 4
    virtual void onLeave(AsmListener* listener);  // slot 5
    virtual void update(float dt, AsmListener* listener);  // slot 6
    virtual void setLocalTime(float time);  // slot 7
    virtual float getLocalTime() const;  // slot 8
    virtual void onSetSpeed();  // slot 9
    virtual void onSetWeight();  // slot 10
    virtual AsmClip* getBaseClip() const;  // slot 11

    AsmClip m_clip;  // the name is not the original's
};
}  // namespace anm

#endif
