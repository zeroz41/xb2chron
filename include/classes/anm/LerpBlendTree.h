#ifndef CLASSES_ANM_LERPBLENDTREE_H
#define CLASSES_ANM_LERPBLENDTREE_H

#include "anm/AsmBlender.h"
#include "mm/mtl/Vector.h"

namespace anm { class AsmListener; }
namespace anm { class Variable; }
namespace anm { struct ResLerpTree; }
namespace anm { struct ResStateData; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B814D8; a state blending its clips by where a float variable lies between their points: the two
// points around the value share the state's weight (the fields' names are not the original's)
class LerpBlendTree : public ::anm::AsmState {
public:
    LerpBlendTree(const ResStateData* pRes, const ResLerpTree* pTree, mm::mtl::Vector<Variable>& variables,
                  mm::mtl::IAllocator& allocator);
    virtual ~LerpBlendTree();  // slot 0
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

    const ResLerpTree* m_pTree;
    AsmClip* m_pClips;          // one per clip of the state, from the allocator
    unsigned int m_clipCount;
    const Variable* m_pVariable;
};
}  // namespace anm

#endif
