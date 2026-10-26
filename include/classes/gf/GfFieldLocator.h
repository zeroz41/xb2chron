#ifndef CLASSES_GF_GFFIELDLOCATOR_H
#define CLASSES_GF_GFFIELDLOCATOR_H

#include "classes/gf/AFieldLocator.h"
#include "gf/QuestID.h"

namespace gmk { class GmkEvent; }
namespace gmk { class GmkPrecious; }

namespace gf {
// table 0x7100B51E70
// a quest's field locator: createByQuest makes the AFieldLocator its CreateInfoByQuest asks for and update() runs it
class GfFieldLocator {
public:
    // what createByQuest builds the locator from (the field names are not the original's)
    struct CreateInfoByQuest {
        CreateInfoByQuest() : m_type(-1), m_id(-1) {}
        QuestID m_questId;  // the quest the locator is made for
        int m_type;         // createByQuest's switch: which locator to make (1: a battle target, ...)
        int m_id;           // the BDAT row createByQuest reads the target's ids from
    };

    GfFieldLocator(const CreateInfoByQuest* info);
    GfFieldLocator(const GfFieldLocator& other);
    virtual ~GfFieldLocator() {  // slot 0
        dispose();
    }
    void createByQuest(const CreateInfoByQuest& info);
    void createLocatorTalkPreorder(unsigned short npcId);
    void createLocatorEventPreorder(const gmk::GmkEvent& event);
    void createLocatorPreciousPreorder(const gmk::GmkPrecious& precious);
    bool isOtherMap() const;
    void dispose();
    void update();
    // whether an icon id is the one BDAT table 0x7b's row 0x10 names for preorders (the parameter name is not the
    // original's)
    static bool isIconIdPreorder(int iconId);

    CreateInfoByQuest m_info;  // 0x8: what createByQuest was given (the name is not the original's)
    AFieldLocator* m_locator;  // 0x18: the locator createByQuest made (the name is not the original's)
};
}  // namespace gf

#endif
