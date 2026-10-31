#ifndef CLASSES_GF_GFACHIEVMANAGER_H
#define CLASSES_GF_GFACHIEVMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "gf/QuestID.h"

namespace gf { class GfAchievManager; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum ActivateType : int; }

namespace gf {
// table 0x7100B52BF0
class GfAchievManager : public ::mm::mtl::PtrSingleton< ::gf::GfAchievManager> {
public:
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
};
}  // namespace gf

#endif
