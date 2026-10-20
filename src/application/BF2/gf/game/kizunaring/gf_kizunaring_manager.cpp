#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfKizunaringManager.h"
#include "gf/GfKizunaringBlade.h"

namespace gf {

GfKizunaringManager::GfKizunaringManager(const GfSetupParam& param) {
    initialize(param);
}

void GfKizunaringManager::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

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

void GfKizunaringManager::finalize() {
    m_initialized = false;
}

void GfKizunaringManager::orderAchievement(unsigned int id) {
    GfKizunaringBlade::orderAchievement(id);
}

void GfKizunaringManager::setupGame() {}

void GfKizunaringManager::qevCompleteQuest(const QuestCompleteParam& param) {
    GfKizunaringBlade::qevCompleteQuest(param);
}

}  // namespace gf
