#include "gf/SDataOption.h"
#include "gf/SDataSave.h"
#include "classes/gf/GfDataStore.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataStore.h"
#include "classes/gf/GfSound.h"

namespace gf {

GfDataStore::~GfDataStore() {}

void GfDataStore::build(const GfSetupParam& param) {
#line 49
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfDataStore(param);
}

void GfDataStore::destroy() {
    GfDataStore* store = get();
    store->m_initialized = false;
    delete store;
}

void GfDataStore::initOptionData() {
    if (GfDataStore* store = get()) {
        store->m_option.clear();
    }
}

SDataGame& GfDataStore::getDataGame() {
    return get()->m_game;
}

SDataSystem& GfDataStore::getDataSystem() {
    return get()->m_system;
}

SDataDriverDlc (&GfDataStore::fn_710022D440())[16] {
    return get()->m_dlcDrivers;
}

SDataOption& GfDataStore::getDataOption() {
    return get()->m_option;
}

void GfDataStore::setupOptionData(const SDataOption& option) {
    if (GfDataStore* store = get()) {
        store->m_option = option;
    }
}

void SSoundUiOption::clear() {
    GfMasterVolume volume;
    m_gamma = 128;
    m_byte1E = 0;
    m_eventSubtitle = true;
    m_volume[0] = static_cast<int>(volume.m_eventVoiceVolume * 255.0f);
    m_volume[1] = static_cast<int>(volume.m_eventCsVolume * 255.0f);
    m_volume[2] = static_cast<int>(volume.m_eventBgmVolume * 255.0f);
    m_volume[3] = static_cast<int>(volume.m_eventSeVolume * 255.0f);
    m_volume[4] = static_cast<int>(volume.m_gameBgmVolume * 255.0f);
    m_volume[5] = static_cast<int>(volume.m_gameEnvVolume * 255.0f);
    m_volume[6] = static_cast<int>(volume.m_gameWeatherVolume * 255.0f);
    m_volume[7] = static_cast<int>(volume.m_gameSeVolume * 255.0f);
    m_volume[8] = static_cast<int>(volume.m_playerVoiceVolume * 255.0f);
    m_volume[9] = static_cast<int>(volume.m_enemyVoiceVolume * 255.0f);
    m_volume[10] = static_cast<int>(volume.m_nareVoiceVolume * 255.0f);
    m_volume[11] = static_cast<int>(volume.m_systemVolume * 255.0f);
    m_volume[12] = static_cast<int>(volume.m_menuBgmVolume * 255.0f);
    fn_710022E334();
}

void SSoundUiOption::fn_710022E334() {
    m_keyA = 0xED;
    m_keyB = 0x1EB0;
    m_keyC = 0x5F;
    m_byte3B = 0;
    memset(m_list, 0, sizeof(m_list));
    m_keyD = 6;
    fn_7100254EF0(this, 0);
    m_flagA = 0;
    m_flagB = 0;
    m_flagC = 0;
    m_flagD = 0;
    m_flagE = 0;
    m_flagF = 0;
}

}  // namespace gf
