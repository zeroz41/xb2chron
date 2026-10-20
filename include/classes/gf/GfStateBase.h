#ifndef CLASSES_GF_GFSTATEBASE_H
#define CLASSES_GF_GFSTATEBASE_H

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table none (its derived classes')
class GfStateBase {
public:
    virtual ~GfStateBase();  // slot 0
    virtual void getName() const = 0;  // slot 2
    virtual void onEnter(void*, ai::State*) = 0;  // slot 3
    virtual void onLeave(void*, ai::State*) = 0;  // slot 4
    virtual void onStep(void*, void const*) = 0;  // slot 5
    virtual void onEvent(void*, void*);  // slot 6
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
};
}  // namespace gf

#endif
