#ifndef CLASSES_GF_GFMENUREFERENCEQUEST_H
#define CLASSES_GF_GFMENUREFERENCEQUEST_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfAllocator.h"
#include "gf/QuestID.h"

// gf_menu_reference_quest.h as the menu files include it: create cites it
#define GF_MENU_REFERENCE_QUEST_PATH "D:/Monolithsoft/BF2/prog/application/BF2\\gf/menu/gf_menu_reference_quest.h"

namespace gf {
// table 0x7100B636C8; a counted quest a menu object shares with GfMenuQuestAdapter (its reference count at 8,
// which GfMenuQuestAdapter::createFromReference adds to). Every virtual is inline: the table is weak, emitted where
// the class is constructed (GfMenuObjMercenaryTop's constructor), D0 and getQuest in that unit's tail.
class GfMenuReferenceQuest : public ::mm::mtl::ReferenceObject {
public:
    GfMenuReferenceQuest() {}  // the symbols name no copy (inline in create)
    virtual ~GfMenuReferenceQuest() {}  // slot 0
    virtual void getQuest(gf::QuestID& quest) const { quest = m_quest; }  // slot 2
    // a new one (GfMenuObjMercenaryTop's constructor holds it; inline: the name is not the original's)
    static GfMenuReferenceQuest* create() {
#line 57 GF_MENU_REFERENCE_QUEST_PATH
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuReferenceQuest();
    }
    // what getQuest copies out; GfMenuObjQuestLog::TitleListener stores the event's quest here (the name is not the
    // original's)
    QuestID m_quest;
};
}  // namespace gf

#endif
