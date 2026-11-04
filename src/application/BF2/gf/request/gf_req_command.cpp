#include "gf/FileStaticVec3.h"
#include "gf/GfReqCommand.h"
#include "gf/GfReqParam.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfScriptManager.h"
#include "classes/gf/GfFobjManager.h"
#include "classes/gf/GfPause.h"
#include "btl/Utility.h"
#include "ml/TimeCount.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataDriver.h"
#include "classes/gf/GfGameSave.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/MapjumpCamera.h"

namespace gf {

// The requests' data (each new'd for GfReqManager::addCommand, which deletes it once the request ran). Every name
// below is inferred, not the original's.

// a save: reqSave, reqSaveForLastGame, reqSoloParty and reqSaveOption fill it
struct ReqSaveParam : public GfReqParam {
    ReqSaveParam() : m_soloParty(false), m_flag(false) {}
    unsigned int m_slot;  // a SAVESLOT, or reqSoloParty's party; reqSaveOption's -1
    bool m_soloParty;     // reqSoloParty's
    bool m_flag;          // reqSaveForLastGame's
};

struct ReqWaitEventParam : public GfReqParam {
    float m_time;
    GF_OBJ_HANDLE* m_handle;
};

struct ReqRebuildPartyWeaponParam : public GfReqParam {
    unsigned int m_party;  // the driver's party id
    int m_bladeIndex;      // the blade's index among the driver's
};

struct ReqChangeBladeWithSetIdParam : public GfReqParam {
    unsigned int m_slot;
    int m_setId;
    bool m_flag;
};

// reqPartySwitchForIra's: it takes no arguments
struct ReqEmptyParam : public GfReqParam {};

// a map execMapjump has jumped to and the controlled mover's position when it left it; the names are not the
// original's
struct MapjumpPos {
    unsigned int m_map;
    mm::Vec3 m_pos;
};

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAEB00)
mm::mtl::RTTI MapjumpCamera::m_rtti("MapjumpCamera", &::fw::Camera::m_rtti, nullptr);
// 2.0.0's symbols name it (by its destructor); the member's name is not the original's
class MapjumpPosition {
public:
    ~MapjumpPosition();
    mm::mtl::FixedVector<MapjumpPos, 1024> m_positions;
};

MapjumpPosition::~MapjumpPosition() {}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAEB20)
static MapjumpPosition s_mapjumpPositions;

struct ReqStartScriptParam : public GfReqParam {
    mm::mtl::FixStr<32> m_name;
    unsigned int m_id;
    bool m_start;
};

unsigned int GfReqCommand::reqSave(SAVESLOT slot) {
#line 139
    ReqSaveParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqSaveParam;
    param->m_slot = slot;
    return GfReqManager::addCommand(param, execSave);
}

unsigned int GfReqCommand::reqSaveForLastGame(SAVESLOT slot) {
#line 147
    ReqSaveParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqSaveParam;
    param->m_slot = slot;
    param->m_flag = true;
    return GfReqManager::addCommand(param, execSave);
}

unsigned int GfReqCommand::reqSaveOption() {
#line 157
    ReqSaveParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqSaveParam;
    param->m_slot = -1;
    return GfReqManager::addCommand(param, execSaveOption);
}

void GfReqCommand::execSaveOption(const GfReqParam* param) {
    const ReqSaveParam* save = static_cast<const ReqSaveParam*>(param);
    GfGameSave gameSave(static_cast<SAVESLOT>(save->m_slot), false, false, false);
    gameSave.execOptionSaveWithMicroThread();
}

unsigned int GfReqCommand::reqSoloParty(unsigned int party) {
#line 165
    ReqSaveParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqSaveParam;
    param->m_slot = party;
    param->m_soloParty = true;
    return GfReqManager::addCommand(param, execSave);
}

unsigned int GfReqCommand::reqWaitEvent(float time, GF_OBJ_HANDLE* handle) {
#line 223
    ReqWaitEventParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqWaitEventParam;
    param->m_time = time;
    param->m_handle = handle;
    return GfReqManager::addCommand(param, execWaitEvent);
}

unsigned int GfReqCommand::reqRebuildPartyWeapon(unsigned int blade) {
#line 238
    ReqRebuildPartyWeaponParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqRebuildPartyWeaponParam;
    unsigned int party = GfGameParty::getPartyId(4, blade);
    if (party == static_cast<unsigned int>(-1)) {
        return -1;
    }
    DataParamAcc driver(GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0)));
    unsigned int driverId = 0;
    if (driver.isValid() && driver.getObjType() == 3) {
        driverId = driver.getBdatId();
    }
    int bladeNum = GfDataDriver::getMaxSetBladeNum(driverId);
    int index = -1;
    for (int i = 0; i < bladeNum; i++) {
        if (driver.getBlade(i, false) == blade) {
            index = i;
            break;
        }
    }
    if (index < 0) {
        return -1;
    }
    param->m_party = party;
    param->m_bladeIndex = index;
    return GfReqManager::addCommand(param, execRebuildPartyWeapon);
}

void GfReqCommand::execWaitEvent(const GfReqParam* param) {
    const ReqWaitEventParam* wait = static_cast<const ReqWaitEventParam*>(param);
    float fadeTime = 0.5f;
    if (wait->m_time >= fadeTime) {
        // wait for an event to be able to start (15 seconds at most), then out the rest of the time
        ml::TimeCount count;
        while (!btl::Utility::IsEnableEventStart()) {
            GfSleep(1);
            if (count.getSecLap() > 15.0f) {
                break;
            }
        }
        float rest = wait->m_time - 0.5f - count.getSecLap();
        while (rest > 0.0f) {
            if (!GfPause::isPause(16)) {
                rest -= GfReqManager::getUpdateInfo().m_deltaTime;
            }
            GfSleep(1);
        }
        fadeTime = 1.5f;
    }
    float time = 0.0f;
    do {
        time += GfReqManager::getUpdateInfo().m_deltaTime;
        if (time > fadeTime) {
            time = fadeTime;
        }
        GfFobjManager::get()->m_waitEventValue = time / fadeTime * 40.0f;
        GfFobjManager::get()->m_waitEvent = true;
        GfSleep(1);
    } while (time < fadeTime);
    GfFobjManager::get()->m_waitEventValue = 1000.0f;
    GfFobjManager::get()->m_waitEvent = false;
    GfSleep(1);
    GfFobjManager::get()->m_waitEventValue = 0.0f;
    GfFobjManager::get()->m_waitEvent = false;
}

unsigned int GfReqCommand::reqChangeBladeWithSetId(unsigned int slot, int setId, bool flag) {
    ReqChangeBladeWithSetIdParam* param =
#line 406
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqChangeBladeWithSetIdParam;
    param->m_slot = slot;
    param->m_setId = setId;
    param->m_flag = flag;
    return GfReqManager::addCommand(param, execChangeBladeWithSetId);
}

void GfReqCommand::execChangeBladeWithSetId(const GfReqParam* param) {
    const ReqChangeBladeWithSetIdParam* change = static_cast<const ReqChangeBladeWithSetIdParam*>(param);
    if (!change->m_flag) {
        // wait up to 10 seconds for the small requests to finish
        float time = 0.0f;
        while (GfReqSmallCom::isExistCommandWithoutParallel()) {
            GfSleep(1);
            time += GfReqManager::getUpdateInfo().m_deltaTime;
            if (time >= 10.0f) {
                break;
            }
        }
    }
    fn_71005573CC(change->m_slot, change->m_setId);
}

unsigned int GfReqCommand::reqPartySwitchForIra() {
#line 427
    ReqEmptyParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqEmptyParam;
    return GfReqManager::addCommand(param, execPartySwitchForIra);
}

unsigned int GfReqCommand::reqDestroyGf() {
#line 1014
    ReqEmptyParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqEmptyParam;
    unsigned int handle = GfReqManager::addCommand(param, execDestroyGf);
    GfReqManager::terminateCommand();
    return handle;
}

unsigned int GfReqCommand::reqStartScript(unsigned int id, const char* name, bool start) {
#line 1119
    ReqStartScriptParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReqStartScriptParam;
    param->m_name = name;
    param->m_start = start;
    param->m_id = id;
    return GfReqManager::addCommand(param, execStartScript);
}

void GfReqCommand::execStartScript(const GfReqParam* param) {
    const ReqStartScriptParam* script = static_cast<const ReqStartScriptParam*>(param);
    GfScriptManager::loadScript(script->m_id, script->m_name.m_str);
    if (script->m_start) {
        GfScriptManager::startScript(script->m_id);
    }
}

}  // namespace gf
