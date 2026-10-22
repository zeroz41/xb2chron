#ifndef CLASSES_GF_GFGAMEMOVERSWITCHER_H
#define CLASSES_GF_GFGAMEMOVERSWITCHER_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfGameMoverSwitcher; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B54E28: swaps the party's leader with the player behind it (the first two of GfGamePlayerFormation's)
class GfGameMoverSwitcher : public ::mm::mtl::PtrSingleton< ::gf::GfGameMoverSwitcher>, public ::fw::MessageObject, public ::gf::IGfEvent {
public:
    // build inlines it (1.0.0 has a copy; 3.0.1 none)
    GfGameMoverSwitcher() : m_enable(false) {}
    virtual ~GfGameMoverSwitcher();  // slot 0
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyMemberOK(bool);  // slot 3
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 4

    static void build(const GfSetupParam& param);
    static void destroy();
    // 1.0.0's (3.0.1 has no copies; build and destroy inline them)
    void setup() { GfEvent::addEventCallback(this); }
    void cleanup() { GfEvent::removeEventCallback(this); }
    void switchMover();

    // whether the leader may be switched: gevPartyMemberOK sets it when the party leader's object is of type 4 and
    // not riding a pair (the name is not the original's)
    bool m_enable;
};
}  // namespace gf

#endif
