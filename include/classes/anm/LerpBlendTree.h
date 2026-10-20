#ifndef CLASSES_ANM_LERPBLENDTREE_H
#define CLASSES_ANM_LERPBLENDTREE_H

namespace anm { class AsmBlender; }
namespace anm { class AsmListener; }

namespace anm {
// table 0x7100B814D8
class LerpBlendTree {
public:
    virtual ~LerpBlendTree();  // slot 0
    virtual void attach(anm::AsmBlender*);  // slot 2
    virtual void dettach(anm::AsmBlender*);  // slot 3
    virtual void onEnter(anm::AsmListener*);  // slot 4
    virtual void onLeave(anm::AsmListener*);  // slot 5
    virtual void update(float, anm::AsmListener*);  // slot 6
    virtual void setLocalTime(float);  // slot 7
    virtual void getLocalTime() const;  // slot 8
    virtual void onSetSpeed();  // slot 9
    virtual void onSetWeight();  // slot 10
    virtual void getBaseClip() const;  // slot 11
};
}  // namespace anm

#endif
