#ifndef CLASSES_ANM_SPEEDLERPBLENDTREE_H
#define CLASSES_ANM_SPEEDLERPBLENDTREE_H

#include "anm/AsmBlender.h"
#include "mm/mtl/Vector.h"

namespace anm { class AsmListener; }
namespace anm { class Variable; }
namespace anm { struct ResSpeedLerpTree; }
namespace anm { struct ResStateData; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B815B8; a state blending its clips as LerpBlendTree does, also scaling their speeds so that the two
// blended clips keep pace with each other and with the variable (the fields' names are not the original's)
class SpeedLerpBlendTree : public ::anm::AsmState {
public:
    SpeedLerpBlendTree(const ResStateData* pRes, const ResSpeedLerpTree* pTree, mm::mtl::Vector<Variable>& variables,
                  mm::mtl::IAllocator& allocator);
    virtual ~SpeedLerpBlendTree();  // slot 0
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
    // the clips' weights and speeds from the variable's value (the spelling is the symbol's)
    void adjustSpeesAndWeight();

    const ResSpeedLerpTree* m_pTree;
    AsmClip* m_pClips;          // one per clip of the state, from the allocator
    unsigned int m_clipCount;
    const Variable* m_pVariable;
};
}  // namespace anm

#endif
