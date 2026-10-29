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
    void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);
};
}  // namespace gf

#endif
