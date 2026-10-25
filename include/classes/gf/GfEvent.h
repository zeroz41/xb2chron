#ifndef CLASSES_GF_GFEVENT_H
#define CLASSES_GF_GFEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { enum GEV : int; }  // as IGfEvent.h declares it
namespace gf { class GF_OBJ_HANDLE; enum ActivateType : int; }
namespace gf { class GfSetupParam; }
namespace gf { class GfEvent; }
namespace gf { class IGfEvent; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B591E8
class GfEvent : public ::mm::mtl::PtrSingleton< ::gf::GfEvent> {
public:
    // the event for a driver changing its engaged blade from one slot to another
    static void callBladeChange(GF_OBJ_HANDLE* handle, int from, int to);
    static void callHikariCurrent(bool hikari);
    static void callBladeActivate(unsigned int blade, ActivateType from, ActivateType to);  // GfGameUtil::changeHikariCurrent passes its flag
    static void build(const GfSetupParam& param);
    static void destroy();
    static void callTargetAccess(GF_OBJ_HANDLE*);
    static void callItemAdd(unsigned int item, int count);  // count of the item gained (or lost)
    static void callTargetChange(GF_OBJ_HANDLE*);
    // a party driver's object entering (true) or leaving (false) the game, with its setup's party id
    // (GfGameParty::gevGameObjEnter and gevGameObjLeave; 1.0.0's symbol)
    static void callPartyDriver(GF_OBJ_HANDLE* handle, unsigned int partyId, bool enter);
    static void callPartyMemberOK(bool ok);  // GfGameParty::update: the party's objects are ready (or not any more)
    static void callChangeLeader(GF_OBJ_HANDLE* leader);  // GfGameParty::update: the party leader changed
    static void callPartyIDMemberOK(bool ok, unsigned int partyId);
    // GfPlayComCallbackEventSequence::start passes 12 (begin) or 13 and its id
    static void callEventPlay(GEV gev, unsigned int id);
    virtual ~GfEvent();  // slot 0
    static void callCameraControl(int type);
    // listener joins (leaves) the ones GfEvent's calls reach
    static void addEventCallback(IGfEvent* listener);
    static void removeEventCallback(IGfEvent* listener);
    // each listener's gevGameMapModel (GfMapManager::destroyMapData passes the map's object and false)
    static void callGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    static void callGameState(GF_STATE prev, GF_STATE next);  // each listener's gevGameState
    static void callExecState(EXEC_STATE state);  // each listener's gevExecState
    static void callLoadGameTime(float time);  // each listener's gevLoadGameTime
    static void callSwapFormation(unsigned int index0, unsigned int index1);  // each listener's gevSwapFormation
    // each listener told the salvage game's state (1.0.0's name: 3.0.1's symbols spell it fn_7100326DF8)
    static void callSalvageStateChange(unsigned int state);
    static void callBladeUnselect(unsigned int blade, bool unselect);  // GfDataBlade::setUnselect
    // GfDataBlade::setTrustPoint passes 4, the blade, 0, 0
    static void callDebugChangeIdea(unsigned int, unsigned int, unsigned int, unsigned int);
};
}  // namespace gf

#endif
