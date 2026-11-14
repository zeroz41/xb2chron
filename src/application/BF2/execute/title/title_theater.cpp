// the title's event theater checks (tl::TitleTheaterUtil, new in 3.0.1)

#include "classes/tl/TitleTheaterUtil.h"
#include "classes/tl/TitleMain.h"
#include "gf/GfDataEvent.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestID.h"
#include "gf/SDataGame.h"
#include "gf/SDataSaveIra.h"

namespace tl {

namespace {
// a quest and the event it opens in the theater (the names are not the original's)
struct OrderedQuestEvent {
    unsigned short m_event;
    unsigned short m_quest;
    bool m_needFinish;  // the quest must be finished (state 2 and above), not only ordered
};

// lbl_71009B9548 (the name is not the original's)
const OrderedQuestEvent s_orderedQuestEvents[19] = {
    {0x50F4, 0x138A, false}, {0x5254, 0x1493, false}, {0x5260, 0x1498, false}, {0x5296, 0x14C4, false},
    {0x5234, 0x1477, false}, {0x52AD, 0x14D1, false}, {0x524B, 0x148C, false}, {0x52D8, 0x14DE, false},
    {0x52DA, 0x14DF, true},  {0x5155, 0x13CF, false}, {0x5168, 0x13DB, false}, {0x527B, 0x14AB, false},
    {0x52A4, 0x14CA, false}, {0x513C, 0x13C7, true},  {0x51C9, 0x1423, false}, {0x50EF, 0x0A15, true},
    {0x5217, 0x146E, true},  {0x51E7, 0x142D, true},  {0x51F3, 0x1435, true},
};
}  // namespace

void TitleTheaterUtil::setEventPlayFlagByOrderedQuest(gf::SDataGame& game) {
    for (unsigned long i = 0; i < 19; i++) {
        int state = gf::GfQuestInfo::getState(game, gf::QuestID(s_orderedQuestEvents[i].m_quest));
        if (s_orderedQuestEvents[i].m_needFinish) {
            if (state < 2) {
                continue;
            }
        } else if (state == 0) {
            continue;
        }
        gf::GfDataEvent::setWatchedEventFlag(game, s_orderedQuestEvents[i].m_event);
    }
}

bool TitleTheaterUtil::isDefaultWeaponEvent(unsigned int event) {
    // a loop over a constant list: clang unrolls it into the original's three bit-test ranges (the list's order is
    // not known; the array leaves no data)
    static const unsigned int s_events[] = {0x51D2, 0x51FE, 0x5202, 0x5208, 0x5241, 0x524B,
                                            0x5255, 0x5256, 0x5257, 0x5262, 0x5296, 0x5297};
    for (unsigned int i = 0; i < 12; i++) {
        if (s_events[i] == event) {
            return true;
        }
    }
    return false;
}

bool TitleTheaterUtil::isNeedCheckSavedEvent(unsigned int event) {
    bool hasTitle = TitleMain::get() != nullptr;
    bool isEvent = event - 10200 < 2;
    return hasTitle && isEvent;
}

bool TitleTheaterUtil::isOpenSavedEvent(unsigned int event) {
    if (isNeedCheckSavedEvent(event)) {
        return gf::GfDataEvent::isSavedEvent(event, TitleMain::get()->getSaveBuffer()->m_game);
    }
    return false;
}

}  // namespace tl
