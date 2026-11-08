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
#include "classes/gf/GfDataZlib.h"
#include "classes/gf/LoadIraSaveData.h"
#include "classes/gf/GfInfo.h"
#include "classes/ml/Thread.h"
#include "ml/DevFileParamTh.h"
#include "ml/WorkRootMem.h"
#include "mtl/MemManager.h"
#include "nn/util.h"
#include "nn/fs.h"
#include "nn/ec.h"
#include "classes/ml/DevFileNxTh.h"
#include "gf/GfGameUtilDiff.h"
#include <string.h>

namespace gf {

namespace _gfgsv {
// named by 1.0.0 (_ZN2gf6_gfgsv11s_SDataSaveE; the symbols leave 3.0.1's unnamed, lbl_7100D6CCA0)
SDataSaveIra s_SDataSave;
SDataOption s_SDataOption;
// the mount LoadIraSaveData::loadData reads the Torna save from
const char* aIraMount = "ira";
}  // namespace _gfgsv

SDataSaveIra* GfGameSave::getGameSaveData() {
    return &_gfgsv::s_SDataSave;
}

SDataSaveIra* GfGameSave::getIraGameSaveData() {
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
        GfDataSave::getFileNameForIraOptionBin(name);
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

GfDataZlib::Buffer* GfDataZlib::execForSave(const void* src, unsigned long size) {
    m_compress.clear();
    m_compress.m_src = src;
    m_compress.m_srcSize = size;
    if (GfIsMicroThread()) {
        ml::Thread* thread = ml::Thread::create("CompressThread", false, fnThreadSave, this, 0x10000, ml::CPUID(2), 0);
        if (thread != nullptr) {
            thread->resume();
            while (!thread->isTerminated()) {
                GfSleep(1);
            }
            thread->release();
        }
    } else {
        execCompress();
    }
    return &m_compress;
}

GfGameLoad::GfGameLoad(SAVESLOT slot)
    : m_ira(GfGameManager::isGameTypeIra()), m_slot(slot), m_saveData(nullptr), m_optionData(nullptr), m_state(0),
      m_fileHandle(nullptr), m_fileKind(0), m_fileResult(-1), m_dest(nullptr), m_copyDest(nullptr),
      m_readData(nullptr), m_readSize(0) {}

GfGameLoad::~GfGameLoad() {}

bool GfGameLoad::execGameLoadWithMicroThread(SDataSaveIra& save) {
    m_state = 2;
    mm::mtl::FixStr<256> name;
    m_dest = &save;
    save.m_system.m_version = 0;
    m_saveData = new (getAllocator(ALLOCATOR(0))->allocate((sizeof(SDataSaveIra) + 0xF) & ~0xFUL, 0x10)) SDataSaveIra();
    m_saveData->m_system.m_version = 0;
    m_readData = m_saveData;
    if (m_ira) {
        m_readSize = sizeof(SDataSaveIra);
    } else {
        m_readSize = sizeof(SDataSystem) + sizeof(SDataGame);
    }
    getGameFileNameBin(name);
    // (inlined in both loads: its parameter lies above the name on the stack)
    [&]() {
        ml::DevFileParamTh param;
        param.m_path = name.m_str;
        param.m_buffer = m_readData;
        unsigned int size = m_readSize;
        param.m_size = (size & 0xF) != 0 ? size + 0x10 - (size & 0xF) : size;
        param.m_listener = this;
        m_fileHandle = ml::DevFileTh::readFile(param);
    }();
    while (m_fileHandle != nullptr) {
        GfSleep(1);
    }
    phaseBinData();
    m_state = 0;
    if (save.m_game.m_areaStamp != 0x3E9F2CB8) {
        save.m_game.m_areaStamp = 0x3E9F2CB8;
        memset(save.m_game.m_stampedArea, 0, sizeof(save.m_game.m_stampedArea));
    }
    return save.m_system.m_version == 0x3A15B;
}

bool GfGameLoad::execDirectImportIraGameWithMicroThread(SDataSaveIra& save) {
    m_ira = true;
    m_state = 2;
    mm::mtl::FixStr<256> name;
    m_dest = &save;
    save.m_system.m_version = 0;
    m_saveData = new (getAllocator(ALLOCATOR(0))->allocate((sizeof(SDataSaveIra) + 0xF) & ~0xFUL, 0x10)) SDataSaveIra();
    m_saveData->m_system.m_version = 0;
    m_readData = m_saveData;
    if (m_ira) {
        m_readSize = sizeof(SDataSaveIra);
    } else {
        m_readSize = sizeof(SDataSystem) + sizeof(SDataGame);
    }
    getGameFileNameBin(name);
    LoadIraSaveData loader;
    m_fileResult = loader.execLoad(m_saveData, sizeof(SDataSaveIra));
    phaseBinData();
    m_state = 0;
    if (save.m_game.m_areaStamp != 0x3E9F2CB8) {
        save.m_game.m_areaStamp = 0x3E9F2CB8;
        memset(save.m_game.m_stampedArea, 0, sizeof(save.m_game.m_stampedArea));
    }
    return save.m_system.m_version == 0x3A15B;
}

int LoadIraSaveData::execLoad(void* data, unsigned long size) {
    m_data = data;
    m_size = size;
    if (GfIsMicroThread()) {
        ml::Thread* thread = ml::Thread::create("LoadIraSaveData", false, fnThreadLoad, this, 0x10000, ml::CPUID(2), 0);
        if (thread != nullptr) {
            thread->resume();
            while (!thread->isTerminated()) {
                GfSleep(1);
            }
            thread->release();
        }
    }
    return m_result;
}

bool GfGameLoad::execOptionLoadWithMicroThread(SDataOption& option) {
    m_state = 2;
    mm::mtl::FixStr<256> name;
    m_copyDest = &option;
    option.m_version = 0;
    m_optionData = new (getAllocator(ALLOCATOR(0))->allocate((sizeof(SDataOption) + 0xF) & ~0xFUL, 0x10)) SDataOption();
    m_optionData->m_version = 0;
    m_readData = m_optionData;
    m_readSize = sizeof(SDataOption);
    getOptionFileNameBin(name);
    // (inlined in both loads: its parameter lies above the name on the stack)
    [&]() {
        ml::DevFileParamTh param;
        param.m_path = name.m_str;
        param.m_buffer = m_readData;
        unsigned int size = m_readSize;
        param.m_size = (size & 0xF) != 0 ? size + 0x10 - (size & 0xF) : size;
        param.m_listener = this;
        m_fileHandle = ml::DevFileTh::readFile(param);
    }();
    while (m_fileHandle != nullptr) {
        GfSleep(1);
    }
    phaseBinData();
    m_state = 0;
    if (option.m_soundUi.isUninitializeReserverArea()) {
        option.m_soundUi.initializeReserverArea();
    }
    GfGameUtilDiff::setCustomFollow(option);
    return option.m_version == 0x3A15B;
}

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


GfDataZlib::Buffer* GfDataZlib::execForLoad(const void* src, unsigned long size) {
    m_decompress.clear();
    m_decompress.m_src = src;
    m_decompress.m_srcSize = size;
    if (GfIsMicroThread()) {
        ml::Thread* thread = ml::Thread::create("DecompressThread", false, fnThreadLoad, this, 0x10000, ml::CPUID(2), 0);
        if (thread != nullptr) {
            thread->resume();
            while (!thread->isTerminated()) {
                GfSleep(1);
            }
            thread->release();
        }
    } else {
        execDecompress();
    }
    return &m_decompress;
}

unsigned int GfDataZlib::fnThreadSave(void* argument) {
    if (argument != nullptr) {
        static_cast<GfDataZlib*>(argument)->execCompress();
    }
    return 0;
}

void GfDataZlib::execCompress() {
    unsigned long capacity = m_compress.m_srcSize + 0x10;
    m_compress.setOut(static_cast<unsigned char*>(
        mtl::MemManager::allocate(ml::WorkRootMem::getMemTMP(), capacity, 0x10, false, "no name", 0)));
    memset(m_compress.m_out, 0, capacity);
    const unsigned char header[0x10] = {0x7E, 0xC0, 0xE2, 0xC9, 0x45, 0x98, 0xCE, 0x03,
                                        0xA7, 0x98, 0xF1, 0x33, 0x6A, 0xE7, 0x25, 0x80};
    memcpy(m_compress.m_out, header, sizeof(header));
    void* work = mtl::MemManager::allocate(ml::WorkRootMem::getMemTMP(), 0x41730, 0x10, false, "no name", 0);
    unsigned long size;
    nn::util::CompressZlib(&size, m_compress.m_out + 0x10, m_compress.m_srcSize, m_compress.m_src,
                           m_compress.m_srcSize, work, 0x41730);
    m_compress.m_outSize = size + 0x10;
    if (work != nullptr) {
        mtl::MemManager::deallocate(work, 0, false);
    }
}

unsigned int GfDataZlib::fnThreadLoad(void* argument) {
    if (argument != nullptr) {
        static_cast<GfDataZlib*>(argument)->execDecompress();
    }
    return 0;
}

void GfDataZlib::execDecompress() {
    const unsigned char* src = static_cast<const unsigned char*>(m_decompress.m_src) + 0x10;
    unsigned long srcSize = m_decompress.m_srcSize - 0x10;
    m_decompress.setOut(static_cast<unsigned char*>(
        mtl::MemManager::allocate(ml::WorkRootMem::getMemTMP(), sizeof(SDataSaveIra) * 2, 0x10, false, "no name", 0)));
    memset(m_decompress.m_out, 0, sizeof(SDataSaveIra) * 2);
    void* work = mtl::MemManager::allocate(ml::WorkRootMem::getMemTMP(), 0x1BF0, 0x10, false, "no name", 0);
    nn::util::DecompressZlib(m_decompress.m_out, sizeof(SDataSaveIra) * 2, src, srcSize, work, 0x1BF0);
    if (work != nullptr) {
        mtl::MemManager::deallocate(work, 0, false);
    }
    m_decompress.m_outSize = sizeof(SDataSaveIra);
}

unsigned int LoadIraSaveData::fnThreadLoad(void* argument) {
    if (argument != nullptr) {
        static_cast<LoadIraSaveData*>(argument)->loadData();
    }
    return 0;
}


void LoadIraSaveData::loadData() {
    if (m_data == nullptr || m_size == 0) {
        return;
    }
    mm::mtl::FixStr<256> path(_gfgsv::aIraMount);
    path += ":/";
    path += GfDataSave::getIraSaveDataFileName();
    path += GfDataSave::getSaveDataExtNameForBin();
    // the Torna application's id
    nn::ApplicationId id = {0x0100C9F009F7A000};
    nn::account::Uid uid = {};
    nn::account::GetUserId(&uid, ml::DevFileNxTh::m_appuser);
    if (!nn::fs::IsSaveDataExisting(id, uid)) {
        return;
    }
    if (nn::fs::MountSaveDataReadOnly(_gfgsv::aIraMount, id, uid).IsFailure()) {
        return;
    }
    nn::fs::FileHandle handle;
    if (nn::fs::OpenFile(&handle, path.m_str, nn::fs::OpenMode_Read).IsSuccess()) {
        long size = 0;
        if (nn::fs::GetFileSize(&size, handle).IsSuccess() &&
            nn::fs::ReadFile(handle, 0, m_data, size).IsSuccess()) {
            m_result = size;
            nn::fs::CloseFile(handle);
        }
    }
    nn::fs::Unmount("ira");
}

}  // namespace gf
