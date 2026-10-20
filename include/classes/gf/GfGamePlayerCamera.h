#ifndef CLASSES_GF_GFGAMEPLAYERCAMERA_H
#define CLASSES_GF_GFGAMEPLAYERCAMERA_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// a base of gf::GfGamePlayerCamera no evidence names yet
class TUnk_B55430 {
public:
    virtual ~TUnk_B55430();
    virtual void recieveMessage(fw::MessageObject*, fw::Message&) = 0;
    virtual void gevPartyMemberOK(bool) = 0;
};
// table 0x7100B55430; base at 0x0 unknown (TUnk_B55430)
class GfGamePlayerCamera : public TUnk_B55430, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    virtual ~GfGamePlayerCamera();  // slot 0
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyMemberOK(bool);  // slot 3
};
}  // namespace gf

#endif
