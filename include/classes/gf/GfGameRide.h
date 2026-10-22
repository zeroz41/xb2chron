#ifndef CLASSES_GF_GFGAMERIDE_H
#define CLASSES_GF_GFGAMERIDE_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameRide; }

namespace gf {
// table 0x7100B55BC0
class GfGameRide : public ::mm::mtl::PtrSingleton< ::gf::GfGameRide>, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    // whether the object behind handle is a vehicle
    static bool isVehicle(gf::GF_OBJ_HANDLE* handle);
    virtual ~GfGameRide();  // slot 0
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 3
    static bool isRideOnPair();
};
}  // namespace gf

#endif
