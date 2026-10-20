#ifndef CLASSES_GF_GFGAMEMOVERSWITCHER_H
#define CLASSES_GF_GFGAMEMOVERSWITCHER_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// a base of gf::GfGameMoverSwitcher no evidence names yet
class TUnk_B54E28 {
public:
    virtual ~TUnk_B54E28();
    virtual void recieveMessage(fw::MessageObject*, fw::Message&) = 0;
    virtual void gevPartyMemberOK(bool) = 0;
    virtual void gevPartyReturnFieldState(unsigned int) = 0;
};
// table 0x7100B54E28; base at 0x0 unknown (TUnk_B54E28)
class GfGameMoverSwitcher : public TUnk_B54E28, public ::fw::MessageObject, public ::gf::IGfEvent {
public:
    virtual ~GfGameMoverSwitcher();  // slot 0
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyMemberOK(bool);  // slot 3
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 4
};
}  // namespace gf

#endif
