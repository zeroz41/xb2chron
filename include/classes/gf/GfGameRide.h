#ifndef CLASSES_GF_GFGAMERIDE_H
#define CLASSES_GF_GFGAMERIDE_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// a base of gf::GfGameRide no evidence names yet
class TUnk_B55BC0 {
public:
    virtual ~TUnk_B55BC0();
    virtual void recieveMessage(fw::MessageObject*, fw::Message&) = 0;
    virtual void gevPartyReturnFieldState(unsigned int) = 0;
};
// table 0x7100B55BC0; base at 0x0 unknown (TUnk_B55BC0)
class GfGameRide : public TUnk_B55BC0, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    virtual ~GfGameRide();  // slot 0
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 3
};
}  // namespace gf

#endif
