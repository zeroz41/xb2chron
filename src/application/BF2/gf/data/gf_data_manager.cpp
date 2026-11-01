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

namespace gf {

template <ItemType::Type TYPE, int N, int M>
unsigned int GfDataManager::fn_7100223974(const GfItemInfo (&list)[N], const GfItemInfo (&box)[M], unsigned short id) {
    unsigned int count = 0;
    for (int i = 0; i < N; i++) {
        if (list[i].getIndex() == id) {
            count += list[i].m_count;
        }
    }
    for (const GfItemInfo* it = box; it != box + M; it++) {
        if (it->getIndex() == id) {
            count += it->m_count;
        }
    }
    return count;
}

unsigned int GfDataManager::fn_7100223650(const ItemBox* box, const SDataGame::ItemBoxEx* boxEx, unsigned int item) {
    ItemType::Type type;
    unsigned int id;
    if (!GfDataItem::getItemType(type, id, item)) {
        return 0;
    }
    switch (type) {
    case 1:
        return fn_7100223974<static_cast<ItemType::Type>(1)>(box->m_type1, boxEx->m_type1, id);
    case 2:
        return fn_7100223974<static_cast<ItemType::Type>(2)>(box->m_type2, boxEx->m_type2, id);
    case 3:
        return fn_7100223974<static_cast<ItemType::Type>(3)>(box->m_type3, boxEx->m_type3, id);
    case 5:
        return fn_7100223974<static_cast<ItemType::Type>(5)>(box->m_type5, boxEx->m_type5, id);
    case 6:
        return fn_7100223974<static_cast<ItemType::Type>(6)>(box->m_type6, boxEx->m_type6, id);
    case 14:
        return fn_7100223974<static_cast<ItemType::Type>(14)>(box->m_type14, boxEx->m_type14, id);
    case 15:
        return fn_7100223974<static_cast<ItemType::Type>(15)>(box->m_type15, boxEx->m_type15, id);
    case 7:
        return fn_7100223974<static_cast<ItemType::Type>(7)>(box->m_type7, boxEx->m_type7, id);
    case 8:
        return fn_7100223974<static_cast<ItemType::Type>(8)>(box->m_type8, boxEx->m_type8, id);
    case 9:
        return fn_7100223974<static_cast<ItemType::Type>(9)>(box->m_type9, boxEx->m_type9, id);
    case 10:
        return fn_7100223974<static_cast<ItemType::Type>(10)>(box->m_type10, boxEx->m_type10, id);
    case 11:
        return fn_7100223974<static_cast<ItemType::Type>(11)>(box->m_type11, boxEx->m_type11, id);
    case 12:
        return fn_7100223974<static_cast<ItemType::Type>(12)>(box->m_type12, boxEx->m_type12, id);
    case 16:
        return fn_7100223974<static_cast<ItemType::Type>(16)>(box->m_type16, boxEx->m_type16, id);
    case 17:
        return fn_7100223974<static_cast<ItemType::Type>(17)>(box->m_type17, boxEx->m_type17, id);
    case 18:
        return fn_7100223974<static_cast<ItemType::Type>(18)>(box->m_type18, boxEx->m_type18, id);
    case 19:
        return fn_7100223974<static_cast<ItemType::Type>(19)>(box->m_type19, boxEx->m_type19, id);
    case 20:
        return fn_7100223974<static_cast<ItemType::Type>(20)>(box->m_type20, boxEx->m_type20, id);
    default:
        return 0;
    }
}

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

SDataDlc* GfDataManager::fn_7100224A10() {
    return &GfDataStore::fn_710022D440();
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
