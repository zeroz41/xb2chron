#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfDataStore.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataUtil.h"
#include "gf/gf_data_aoc.h"
#include "gf/GfDataItem.h"
#include "gf/ItemCountLowLevel.h"
#include "gf/GfDataHitonowa.h"

namespace gf {

template <typename List, typename Box>
unsigned int getLowLevelCount(List& list, Box& box, unsigned short id) {
    unsigned int count = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i].getIndex() == id) {
            count += list[i].m_count;
        }
    }
    for (const GfItemInfo* it = box.begin(); it != box.end(); it++) {
        if (it->getIndex() == id) {
            count += it->m_count;
        }
    }
    return count;
}

unsigned int ItemCountLowLevel::getCount(const ItemBox& box, const ItemBoxEx& boxEx, unsigned int item) {
    ItemType::Type type;
    unsigned int id;
    if (!GfDataItem::getItemType(type, id, item)) {
        return 0;
    }
    switch (type) {
    case 1:
        return getLowLevelCount(box.m_type1, boxEx.m_type1, id);
    case 2:
        return getLowLevelCount(box.m_type2, boxEx.m_type2, id);
    case 3:
        return getLowLevelCount(box.m_type3, boxEx.m_type3, id);
    case 5:
        return getLowLevelCount(box.m_type5, boxEx.m_type5, id);
    case 6:
        return getLowLevelCount(box.m_type6, boxEx.m_type6, id);
    case 14:
        return getLowLevelCount(box.m_type14, boxEx.m_type14, id);
    case 15:
        return getLowLevelCount(box.m_type15, boxEx.m_type15, id);
    case 7:
        return getLowLevelCount(box.m_type7, boxEx.m_type7, id);
    case 8:
        return getLowLevelCount(box.m_type8, boxEx.m_type8, id);
    case 9:
        return getLowLevelCount(box.m_type9, boxEx.m_type9, id);
    case 10:
        return getLowLevelCount(box.m_type10, boxEx.m_type10, id);
    case 11:
        return getLowLevelCount(box.m_type11, boxEx.m_type11, id);
    case 12:
        return getLowLevelCount(box.m_type12, boxEx.m_type12, id);
    case 16:
        return getLowLevelCount(box.m_type16, boxEx.m_type16, id);
    case 17:
        return getLowLevelCount(box.m_type17, boxEx.m_type17, id);
    case 18:
        return getLowLevelCount(box.m_type18, boxEx.m_type18, id);
    case 19:
        return getLowLevelCount(box.m_type19, boxEx.m_type19, id);
    case 20:
        return getLowLevelCount(box.m_type20, boxEx.m_type20, id);
    default:
        return 0;
    }
}

inline void GfDataManager::initialize(const GfSetupParam& param) {
    GfDataBdat::build(param);
    GfGameFlag::build(param);
    GfDataStore::build(param);
    GfDataAoc::build(param);
    GfDataHitonowa::initialize();
    GfEvent::addEventCallback(this);
    m_initialized = true;
}

inline void GfDataManager::finalize() {
    GfEvent::removeEventCallback(this);
    GfDataHitonowa::finalize();
    GfDataStore::destroy();
    GfGameFlag::destroy();
    GfDataBdat::destroy();
    GfDataAoc::destroy();
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
    unsigned int prevFlag = GfDataUtil::getScenarioFlag();
    GfDataStore::clear();
    GfGameFlag::clear();
    GfEvent::callChangeScenarioFlag(GfDataUtil::getScenarioFlag(), prevFlag);
}

void GfDataManager::setupGame(const SDataSystem* system, const SDataGame* game, const SDataOption* option,
                              const SDataGameIra* ira) {
    GfDataStore::setGameData(system, game, option, ira);
    GfDataUtil::convertNewCollectFlagPatch();
    GfDataHitonowa::bdatRefresh();
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

SDataDlc* GfDataManager::getDataGameIra() {
    return &GfDataStore::getDataGameIra();
}

SDataOption* GfDataManager::getDataOption() {
    return &GfDataStore::getDataOption();
}

void GfDataManager::gevReloadBdat(RELOAD_BDAT type, unsigned int id) {
    if (type == 1) {
        GfDataHitonowa::bdatRefresh();
    }
}

}  // namespace gf
