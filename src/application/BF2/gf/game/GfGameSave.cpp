#include "classes/gf/GfEvent.h"
#include "gf/FileStaticVec3.h"
#include "gf/SDataSaveIra.h"
#include "classes/ml/DevFileTh.h"
#include "classes/gf/GfDataManager.h"
#include "gf/GfDataSave.h"
#include "gf/GfGameUtilSaveData.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfObjManager.h"
#include <new>
#include "classes/gf/GfGameSave.h"
#include "classes/gf/GfGameLoad.h"
#include "gf/SDataOption.h"
#include "mm/mtl/FixStr.h"
#include "ml/PathUtil.h"
#include "classes/gf/GfGameRide.h"
#include "gf/MsgGameRideEvent.h"
#include "gf/MsgPcBattleStart.h"
#include "classes/gf/GfGameTarget.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfObj.h"
#include "fw/Message.h"
#include "gf/GfDataSave.h"
#include "classes/gf/GfGameLoad.h"
#include "ml/EventFileTh.h"

namespace gf {

namespace _gfgsv {
// named by 1.0.0 (_ZN2gf6_gfgsv11s_SDataSaveE; the symbols leave 3.0.1's unnamed, lbl_7100D6CCA0)
SDataSaveIra s_SDataSave;
SDataOption s_SDataOption;
}  // namespace _gfgsv

SDataSaveIra* GfGameSave::getGameSaveData() {
    return &_gfgsv::s_SDataSave;
}

SDataSaveIra* GfGameSave::getGameOptionData() {
    return &_gfgsv::s_SDataSave;
}

void GfGameSave::makeNewGameSaveData() {
    if (GfDataManager::sys() != nullptr) {
        _gfgsv::s_SDataSave.clear();
        _gfgsv::s_SDataOption = *GfDataManager::getDataOption();
    }
}

GfGameSave::GfGameSave(SAVESLOT slot, bool flag30, bool flag31, bool flag32)
    : m_state(0), m_slot(slot), m_saveData(nullptr), m_optionData(nullptr), m_writeData(nullptr), m_writeSize(0),
      m_flag30(flag30), m_flag31(flag31), m_flag32(flag32), m_fileHandle(nullptr), m_fileKind(0) {}

GfGameSave::~GfGameSave() {
    destroySaveData();
}

void GfGameSave::execGameSaveWithMicroThread() {
    m_state = 2;
    mm::mtl::FixStr<256> name;
    createGameSaveData(name);
    m_fileHandle = ml::DevFileTh::writeFile(name.m_str, this, m_writeData, m_writeSize, 0);
    while (m_fileHandle != nullptr) {
        GfSleep(1);
    }
    ml::DevFileTh::flushSave();
    destroySaveData();
    m_state = 0;
}

void GfGameSave::execOptionSaveWithMicroThread() {
    GfEvent::callChangeGameDifficult();
    m_state = 2;
    mm::mtl::FixStr<256> name;
    createOptionSaveData(name);
    m_fileHandle = ml::DevFileTh::writeFile(name.m_str, this, m_writeData, m_writeSize, 0);
    while (m_fileHandle != nullptr) {
        GfSleep(1);
    }
    ml::DevFileTh::flushSave();
    destroySaveData();
    m_state = 0;
}

void GfGameSave::createOptionSaveData(mm::mtl::FixStr<256>& name) {
    m_optionData = new (getAllocator(ALLOCATOR(0))->allocate((sizeof(SDataOption) + 0xF) & ~0xFUL, 0x10)) SDataOption();
    if (GfManager::isExecModeThater() || GfManager::isExecModeAdvertize()) {
        *m_optionData = *GfGameUtilSaveData::getValidOptionData();
    } else {
        GfGameUtilSaveData::setupOptionSaveData(*m_optionData);
    }
    m_writeData = m_optionData;
    m_writeSize = sizeof(SDataOption);
    if (GfGameManager::isGameTypeIra()) {
        GfDataSave::getFileNameForOptionXml(name);
    } else {
        GfDataSave::getFileNameForOptionBin(name);
    }
    GfDataManager::setupOptionData(*m_optionData);
    _gfgsv::s_SDataOption = *m_optionData;
}

bool GfGameSave::OnFileEvent(ml::EventFileTh* event) {
    if (m_fileHandle == event->m_handle) {
        m_fileKind = event->m_kind;
        m_fileHandle = nullptr;
    }
    if (m_state == 1 && m_fileHandle == nullptr) {
        ml::DevFileTh::flushSave();
        destroySaveData();
        m_state = 0;
    }
    return true;
}

GfGameLoad::GfGameLoad(SAVESLOT slot)
    : m_ira(GfGameManager::isGameTypeIra()), m_slot(slot), m_saveData(nullptr), m_optionData(nullptr), m_state(0),
      m_fileHandle(nullptr), m_fileKind(0), m_fileResult(-1), m_dest(nullptr), m_copyDest(nullptr),
      m_readData(nullptr), m_readSize(0) {}

GfGameLoad::~GfGameLoad() {}

bool GfGameLoad::OnFileEvent(ml::EventFileTh* event) {
    if (m_fileHandle == event->m_handle) {
        m_fileKind = event->m_kind;
        if (m_fileKind == 2) {
            m_fileResult = event->m_result;
        }
        m_fileHandle = nullptr;
    }
    if (m_state == 1 && m_fileHandle == nullptr) {
        phaseBinData();
        m_state = 0;
    }
    return true;
}

void GfGameLoad::getGameFileNameBin(mm::mtl::FixStr<256>& out) {
    mm::mtl::FixStr<256> name;
    if (m_fileName.m_nLen != 0) {
        name = m_fileName.m_str;
    } else if (m_ira) {
        GfDataSave::getFileNameForIraLoad(name, m_slot);
    } else {
        GfDataSave::getFileNameForLoad(name, m_slot);
    }
    ml::PathUtil::getNoExtName(out, name.m_str);
    out += GfDataSave::getSaveDataExtNameForBin();
}

void GfGameLoad::getOptionFileNameBin(mm::mtl::FixStr<256>& out) {
    mm::mtl::FixStr<256> name;
    if (m_ira) {
        GfDataSave::getFileNameForIraOption(name);
    } else {
        GfDataSave::getFileNameForOption(name);
    }
    ml::PathUtil::getNoExtName(out, name.m_str);
    out += GfDataSave::getSaveDataExtNameForBin();
}

}  // namespace gf

