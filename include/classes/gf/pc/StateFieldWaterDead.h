#ifndef CLASSES_GF_PC_STATEFIELDWATERDEAD_H
#define CLASSES_GF_PC_STATEFIELDWATERDEAD_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf { namespace pc {
// table 0x7100B69398
class StateFieldWaterDead : public ::gf::GfStateBase {
public:
    virtual ~StateFieldWaterDead();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
};
}}  // namespace gf::pc

#endif
