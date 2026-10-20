#ifndef CLASSES_GF_GFGAMEPLAYERCAMERA_H
#define CLASSES_GF_GFGAMEPLAYERCAMERA_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfGamePlayerCamera; }

namespace gf {
// table 0x7100B55430
class GfGamePlayerCamera : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerCamera>, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    virtual ~GfGamePlayerCamera();  // slot 0
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyMemberOK(bool);  // slot 3
};
}  // namespace gf

#endif
