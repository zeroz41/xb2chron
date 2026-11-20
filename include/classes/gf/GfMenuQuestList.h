#ifndef CLASSES_GF_GFMENUQUESTLIST_H
#define CLASSES_GF_GFMENUQUESTLIST_H

#include "classes/ui/UIListInfo.h"
#include "gf/QuestID.h"

namespace gf {
// table 0x7100B5F760
class GfMenuQuestList : public ::ui::UIListInfo< ::gf::QuestID> {
public:
    // GfMenuObjQuestList::setupList fills it: the base's 0x14 bytes, then two masks
    class SetupParam : public ::ui::UIListInfoBase::SetupParam {
    public:
        // every category, ordered and finished quests (GfMenuObjQuestList::initializeSub's stores before it clears both)
        SetupParam() : m_categoryMask(7), m_stateMask(3) {}
        // which quests setup lists by QuestListAcc::getListQuestCategory: bit 0 category 3, bit 1 category 2,
        // bit 2 category 1 (setupList sets them per tab); the name is not the original's
        unsigned int m_categoryMask;
        // and by state: bit 0 ordered (GfQuestInfo::isQuestOrder), bit 1 finished (isQuestFin); the name is not the
        // original's
        unsigned int m_stateMask;
    };
    virtual ~GfMenuQuestList();  // slot 0
    static GfMenuQuestList* create();
    void setup(const SetupParam& param);
};
}  // namespace gf

#endif
