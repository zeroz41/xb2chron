#ifndef CLASSES_GF_PC_STATEFIELDTALK_H
#define CLASSES_GF_PC_STATEFIELDTALK_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf { namespace pc {
// table 0x7100B680D8
class StateFieldTalk : public ::gf::GfStateBase {
public:
    virtual ~StateFieldTalk();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
};
}}  // namespace gf::pc

#endif
