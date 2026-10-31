#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfDataStore.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataUtil.h"
#include "gf/gf_data_aoc.h"

namespace gf {

inline void GfDataManager::initialize(const GfSetupParam& param) {
    GfDataBdat::build(param);
    GfGameFlag::build(param);
    GfDataStore::build(param);
    TUnk_B4C840::fn_7100222908(param);
    GfDataBlade::fn_71002550E8();
    GfEvent::addEventCallback(this);
    m_initialized = true;
}

inline void GfDataManager::finalize() {
    GfEvent::removeEventCallback(this);
    GfDataBlade::fn_7100255190();
    GfDataStore::destroy();
    GfGameFlag::destroy();
    GfDataBdat::destroy();
    TUnk_B4C840::fn_710022299C();
    m_initialized = false;
}

GfDataManager::GfDataManager(const GfSetupParam& param) : m_initialized(false) {
    initialize(param);
}

GfDataManager::~GfDataManager() {}

void GfDataManager::build(const GfSetupParam& param) {
#line 48
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfDataManager(param);
}

void GfDataManager::destroy() {
    GfDataManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfDataManager::clear() {
    unsigned int prevFlag = GfDataBlade::fn_7100231884();
    GfDataStore::clear();
    GfGameFlag::clear();
    GfEvent::callChangeScenarioFlag(GfDataBlade::fn_7100231884(), prevFlag);
}

void GfDataManager::setupGame(const SDataSystem* system, const SDataGame* game, const SDataOption* option) {
    GfDataStore::setGameData(system, game, option);
    GfDataUtil::convertNewCollectFlagPatch();
    GfDataBlade::fn_7100255238();
}

void GfDataManager::setupOptionData(const SDataOption& option) {
    GfDataStore::setupOptionData(option);
}

SDataSystem* GfDataManager::getDataSystem() {
    return &GfDataStore::getDataSystem();
}

SDataGame* GfDataManager::getDataGame() {
    return &GfDataStore::getDataGame();
}

SDataDriverDlc* GfDataManager::fn_7100224A10() {
    return GfDataStore::fn_710022D440();
}

SDataOption* GfDataManager::getDataOption() {
    return &GfDataStore::getDataOption();
}

void GfDataManager::gevReloadBdat(RELOAD_BDAT type, unsigned int id) {
    if (type == 1) {
        GfDataBlade::fn_7100255238();
    }
}

}  // namespace gf
