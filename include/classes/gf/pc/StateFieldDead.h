#ifndef CLASSES_GF_PC_STATEFIELDDEAD_H
#define CLASSES_GF_PC_STATEFIELDDEAD_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf { namespace pc {
// table 0x7100B681C8
class StateFieldDead : public ::gf::GfStateBase {
public:
    virtual ~StateFieldDead();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*) {}  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
};
}}  // namespace gf::pc

#endif
