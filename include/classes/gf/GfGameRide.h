#ifndef CLASSES_GF_GFGAMERIDE_H
#define CLASSES_GF_GFGAMERIDE_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameRide; }
namespace gf { class GfSetupParam; }
namespace gf { class MsgGameRideEvent; }

namespace gf {
// table 0x7100B55BC0: a driver riding a blade (setRideOn mounts the party's driver on its blade, getDown takes it off)
class GfGameRide : public ::mm::mtl::PtrSingleton< ::gf::GfGameRide>, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    // out of line in 1.0.0, as are setup, cleanup and resetHandles; 3.0.1 keeps no copy
    GfGameRide() { resetHandles(); }
    static void build(const GfSetupParam& param);
    void setup() { GfEvent::addEventCallback(this); }
    static void destroy();
    void cleanup() { GfEvent::removeEventCallback(this); }
    void resetHandles() {
        m_vehicle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        m_rider = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    // whether a driver rides a blade
    static bool testRideOn();
    static void setRideOn(bool on);
    void rideOn();
    void getDown(GF_OBJ_HANDLE* leader);
    // whether the object behind handle is a vehicle
    static bool isVehicle(gf::GF_OBJ_HANDLE* handle);
    virtual ~GfGameRide();  // slot 0
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 3
    static bool isRideOnPair();
    void procMsgGameRideEvent(fw::MessageObject* sender, MsgGameRideEvent& msg);

    // (the names are not the original's) setRideOn's: the blade ridden (isVehicle) and the driver riding it,
    // -1 while none rides
    GF_OBJ_HANDLE* m_vehicle;
    GF_OBJ_HANDLE* m_rider;
};
}  // namespace gf

#endif
