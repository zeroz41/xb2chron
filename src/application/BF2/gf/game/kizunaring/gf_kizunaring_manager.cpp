#include "gf/QuestID.h"
#include "gf/AchievQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestListAcc.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataQuest.h"
#include "gf/QuestTaskParam.h"
#include "gf/QuestCompleteParam.h"
#include "gf/GfKizunaringBlade.h"
#include "classes/gf/GfKizunaringManager.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/GfAllocator.h"
#include "mm/mtl/FixedVector.h"

namespace gf {

GfKizunaringManager::~GfKizunaringManager() {}

void GfKizunaringManager::build(const GfSetupParam& param) {
#line 55
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfKizunaringManager(param);
}

void GfKizunaringManager::destroy() {
    GfKizunaringManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfKizunaringManager::orderAchievement(unsigned int id) {
    GfKizunaringBlade::orderAchievement(id);
}

void GfKizunaringManager::setupGame() {}

void GfKizunaringManager::qevCompleteQuest(const QuestCompleteParam& param) {
    GfKizunaringBlade::qevCompleteQuest(param);
}

}  // namespace gf
