#ifndef CLASSES_GF_SCOM_POPUP_H
#define CLASSES_GF_SCOM_POPUP_H

#include "classes/gf/SCOM.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "gf/QuestID.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AB98
class SCOM_POPUP : public ::gf::SCOM {
public:
    explicit SCOM_POPUP(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long createAffinity(unsigned int, unsigned int, unsigned int);
    static unsigned long createIdea(unsigned int, unsigned int, unsigned int);
    static unsigned long createPouch(unsigned int, unsigned int, unsigned int);
    static unsigned long createDevelop(unsigned int, unsigned int);
    static unsigned long createCrystalOK(unsigned int);
    static unsigned long createQuest(QuestID);
    static unsigned long createMercenaryReturn(unsigned int, unsigned int);
    static unsigned long createMercenaryAdd(unsigned int);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address sits among
    // SCOM_POPUP's create functions in gf_req_scom. What it does: builds the popup request type 8 with the map id,
    // the team and the team's leader (GfDataMercenaries::getTeamLeader) and drops that request from the popup queue
    // (GfMenuObjPopup::fn_710045D48C; its answer is dropped); GfGameMercenaries::cancelMission passes the mission's
    // map id and the team when it cancels a mission whose flag is 3.
    static void fn_7100569D44(unsigned int mapId, unsigned int teamId);
    static unsigned long createArts(unsigned int, unsigned int);
    // queues an affinity chart achievement popup for a blade's skill line and level; the request's ID
    static unsigned long createAchievement(unsigned int blade, unsigned int line, unsigned int level);
    // Placeholder names: nothing in 1.0.0's symbols names them. Members because each builds SCOM_POPUP (its table,
    // type 75) among its create functions. fn_710056A3FC: popup type 10 with 47 once the game started,
    // GfGameManager::fn_71002AC598 holds, item 25443 is in the box and local flag (1, 35337) is set; its argument
    // is unused (callers TUnk_B535D0::RuleTable::fn_7100290598, fn_7100290BAC). fn_710056A4D8: popup type 11 with
    // its three arguments unless the game is starting or GfDataDriver::isActivateUnuse(first) (caller fn_71002E6DCC).
    static unsigned long fn_710056A3FC(unsigned int);
    static unsigned long fn_710056A4D8(unsigned int driver, unsigned int, unsigned int);

    // the names are not the original's: the popup to open, and the frames exec waits first (create sets 20)
    GfMenuObjPopup::OpenParam m_param;
    int m_wait;
};
}  // namespace gf

#endif
