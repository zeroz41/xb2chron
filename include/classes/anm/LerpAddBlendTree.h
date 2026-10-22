#ifndef CLASSES_ANM_LERPADDBLENDTREE_H
#define CLASSES_ANM_LERPADDBLENDTREE_H

#include "anm/AsmBlender.h"
#include "mm/mtl/Vector.h"

namespace anm { class AsmListener; }
namespace anm { class Variable; }
namespace anm { struct ResLerpAddTree; }
namespace anm { struct ResStateData; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B81468; a state playing its base clips at its weight and adding one of the rest: the one whose point
// a float variable's value reaches, weighted by the value over the point (the fields' names are not the original's)
class LerpAddBlendTree : public ::anm::AsmState {
public:
    LerpAddBlendTree(const ResStateData* pRes, const ResLerpAddTree* pTree, mm::mtl::Vector<Variable>& variables,
                     mm::mtl::IAllocator& allocator);
    virtual ~LerpAddBlendTree();  // slot 0
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
    // the clips' weights from the variable's value
    void adjustWeight();

    const ResLerpAddTree* m_pTree;
    AsmClip* m_pClips;          // one per clip of the state, from the allocator
    unsigned int m_clipCount;
    const Variable* m_pVariable;
};
}  // namespace anm

#endif
