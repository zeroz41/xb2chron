#ifndef CLASSES_GF_GFGAMEMOVERSWITCHER_H
#define CLASSES_GF_GFGAMEMOVERSWITCHER_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfGameMoverSwitcher; }

namespace gf {
// table 0x7100B54E28
class GfGameMoverSwitcher : public ::mm::mtl::PtrSingleton< ::gf::GfGameMoverSwitcher>, public ::fw::MessageObject, public ::gf::IGfEvent {
public:
    virtual ~GfGameMoverSwitcher();  // slot 0
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyMemberOK(bool);  // slot 3
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 4
};
}  // namespace gf

#endif
