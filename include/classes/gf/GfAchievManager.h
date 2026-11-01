#ifndef CLASSES_GF_GFACHIEVMANAGER_H
#define CLASSES_GF_GFACHIEVMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixedVector.h"
#include "gf/QuestID.h"

namespace gf { class GfAchievManager; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum ActivateType : int; }
namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B52BF0
class GfAchievManager : public ::mm::mtl::PtrSingleton< ::gf::GfAchievManager> {
public:
    // a quest's count change waiting for update (12 bytes; 1.0.0's flushEventIncAchiev names the type; the field
    // names are not the original's): incleaseAchievCount's arguments
    struct IncQuest {
        QuestID m_questId;
        unsigned int m_count;  // the count before
        unsigned int m_add;    // what was added
        IncQuest() {}
        // by assignment: the original's queue push copies the quest's halves one by one (QuestID::operator=)
        // and the counts as one block, which only the implicit assignment gives
        IncQuest(const IncQuest& other) {
            *this = other;
        }
    };

    // inline: 3.0.1's build inlines it (1.0.0's is out of line and stores nothing else)
    explicit GfAchievManager(const GfSetupParam&) {}
    static void build(const GfSetupParam& param);
    static void destroy();
    // flushes up to 60 waiting count changes
    void update(const fw::UpdateInfo& info);
    void flushEventIncAchiev(const IncQuest& quest);
    void gevItemAdd(unsigned int, int);
    void gevBladeActivate(unsigned int, ActivateType, ActivateType);
    // SCOM_ACHIEV_INC::exec adds its request's value to its achievement counter, for its blades when it has any
    void incAchiev(unsigned int type, int value);
    // AchievQuest::setCountComplete passes the quest, its count before and what it added
    void incleaseAchievCount(QuestID id, unsigned int count, unsigned int add);
    void incAchievWithBlade(unsigned int type, int value, const mm::mtl::FixedVector<unsigned short, 422>& blades);
    virtual ~GfAchievManager();  // slot 0
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_71005661C0 calls it on
    // PtrSingleton<GfAchievManager>'s instance (which it does not read). What it does: for every blade of blades,
    // fn_710028A448(type, value, blade). Its one caller passes type 0x9C.
    void fn_710028A720(unsigned int type, int value, const mm::mtl::FixedVector<unsigned short, 422>& blades);
    void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);
    // adds to list the blades with an affinity chart line of the achievement; whether list holds any
    bool getBladeByAchievementSet(mm::mtl::FixedVector<unsigned short, 422>& list, unsigned int achievement) const;

    // the count changes incleaseAchievCount queues for update (the name is not the original's)
    mm::mtl::FixedQueue<IncQuest, 512> m_incQueue;
};

// Placeholder name: 1.0.0 has it unnamed too (no symbol: file-local in the original; defined in
// gf_achiev_manager.cpp). What it does: for each of the blade's affinity chart lines (9 to 0), finds the line's current
// quest (the first not finished; a finished one without flag bit 0 ends the search) and, when it is ordered and
// counts the statistic type, adds value's count to it. incAchiev, incAchievWithBlade and fn_710028A720 call it.
void fn_710028A448(unsigned int type, int value, unsigned int blade);
}  // namespace gf

#endif
