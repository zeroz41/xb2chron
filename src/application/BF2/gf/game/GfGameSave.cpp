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
#include "classes/gf/GfEvent.h"
#include "fw/Message.h"
#include "gf/GfDataSave.h"
#include "classes/gf/GfGameLoad.h"
#include "ml/EventFileTh.h"

namespace gf {

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
        GfDataSave::fn_710022C2B0(name, m_slot);
    } else {
        GfDataSave::getFileNameForLoad(name, m_slot);
    }
    ml::PathUtil::getNoExtName(out, name.m_str);
    out += GfDataSave::getSaveDataExtNameForBin();
}

void GfGameLoad::getOptionFileNameBin(mm::mtl::FixStr<256>& out) {
    mm::mtl::FixStr<256> name;
    if (m_ira) {
        GfDataSave::fn_710022C894(name);
    } else {
        GfDataSave::getFileNameForOption(name);
    }
    ml::PathUtil::getNoExtName(out, name.m_str);
    out += GfDataSave::getSaveDataExtNameForBin();
}

}  // namespace gf
