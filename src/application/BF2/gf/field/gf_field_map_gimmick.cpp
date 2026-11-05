#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/gmk/GmkCtrlVolSe.h"
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/GmkElevator.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/MenuCommonWindowParam.h"
#include "classes/gmk/WeatherCond.h"
#include "plugin/Bdat.h"
#include "classes/gmk/BootedGmkCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/GmkCamera.h"
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gf/GfFieldMapGimmick.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/BootedGmkCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/GmkCamera.h"
#include "classes/gmk/GmkCtrlVolSe.h"
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfFieldMapGimmick.h"
#include "classes/gmk/GmkJump.h"
#include "classes/gmk/GmkWarp.h"
#include "gf/MsgPcFieldNotifyWallJump.h"
#include "gf/MsgPcFieldNotifyBigJump.h"
#include "gf/MsgPcFieldNotifyWarp.h"
#include "classes/gf/IFieldSeq.h"
#include "classes/gf/AFieldSeq.h"
#include "classes/gf/GfFieldGrave.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gmk/GmkGrave.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComBehaviorGmk.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/ScriptManager.h"
#include "classes/fw/ScriptInfo.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfFieldJump.h"
#include "classes/gf/GfFieldWarp.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfObjUtil.h"
#include "plugin/Bdat.h"
#include "classes/fw/SoundManager.h"
#include "classes/gf/GfFieldMapGimmick.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/gmk/GmkElevator.h"
#include "mm/mtl/FixStr.h"

namespace gf {

AFieldSeq::AFieldSeq(const GfSetupParam&)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_seq(nullptr), m_isEnd(false), m_isFsSucceeded(false) {}

void AFieldSeq::gevMapjump(GEV ev, const MapjumpCallbackInfo&) {
    if (ev == GEV(1)) {
        dispose();
    }
}

void AFieldSeq::create(GF_OBJ_HANDLE* handle) {
    dispose();
    m_handle = handle;
    m_seq = &AFieldSeq::seqCheckFs;
}

void AFieldSeq::dispose() {
    m_isEnd = false;
    m_isFsSucceeded = false;
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_seq = nullptr;
}

void AFieldSeq::update(float dt) {
    if (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_seq) {
        (this->*m_seq)(dt);
    }
}

void AFieldSeq::seqCheckFs(float) {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle);
    if (gmk == nullptr) {
        dispose();
        return;
    }
    unsigned short fsId = static_cast<unsigned short>(
        Bdat::getValCheck(gmk->getBindedBdatFp(), "FSID", gmk->m_createInfo.m_bdatId, 2));
    unsigned int nameMsId = 0;
    GfGameUtil::getNameMsId(nameMsId, m_handle);
    if (fsId) {
        m_isFsSucceeded = GfGameUtil::evalSumFs(fsId, nameMsId);
    } else {
        m_isFsSucceeded = true;
    }
    if (m_isFsSucceeded) {
        if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
            obj->pad_110 &= ~7;
        }
    }
    m_seq = &AFieldSeq::seqWaitUIEnd;
}

void AFieldSeq::seqWaitUIEnd(float) {
    if (GfMenuFieldSkill::isRunning()) {
        return;
    }
    if (m_isFsSucceeded) {
        GfObjAcc acc(m_handle);
        if (acc.m_obj != nullptr) {
            if (GfComBehaviorGmk* behavior = acc.getObj()->getComponent<GfComBehaviorGmk>(6)) {
                behavior->disposeMenuObj();
            }
        }
        onFsSucceeded();
    } else {
        onFsFailed();
    }
    m_seq = nullptr;
    m_isEnd = true;
}

bool AFieldSeq::isEnd() const {
    return m_isEnd;
}

GfFieldGrave::GfFieldGrave(const GfSetupParam&) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_seq(nullptr) {}

void GfFieldGrave::gevMapjump(GEV ev, const MapjumpCallbackInfo&) {
    if (ev == GEV(1)) {
        dispose();
    }
}

void GfFieldGrave::create(GF_OBJ_HANDLE* handle) {
    dispose();
    m_handle = handle;
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle);
    GfMenuManager::openCommonWindowWithNamed(
        51,
        gmk != nullptr ? static_cast<const gmk::GmkGrave::BdatInfo*>(gmk->m_createInfo.m_bdatInfo)->m_windowArg : 0);
    m_seq = &GfFieldGrave::seqWaitToSelect;
}

void GfFieldGrave::seqWaitToSelect(float) {
    if (GfMenuManager::isOpenCommonWindow()) {
        return;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        if (gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle)) {
            static_cast<gmk::GmkGrave*>(gmk)->reqPopEnemy();
        } else {
            dispose();
        }
    }
    m_seq = nullptr;
    m_isEnd = true;
}

void GfFieldGrave::dispose() {
    if (GfMenuManager::isOpenCommonWindow()) {
        GfMenuManager::closeCommonWindow();
    }
    m_isEnd = false;
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_seq = nullptr;
}

void GfFieldGrave::update(float dt) {
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

void GfFieldGmkTutorial::build(const GfSetupParam&) {
#line 1437
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldGmkTutorial();
}

void GfFieldGmkTutorial::destroy() {
    GfFieldGmkTutorial* tutorial = get();
    tutorial->dispose();
    delete tutorial;
}

void GfFieldGmkTutorial::dispose() {
    m_arg = 0;
    m_name.clear();
}

void GfFieldGmkTutorial::create(const char* name, unsigned int arg) {
    dispose();
    m_name = name;
    m_arg = arg;
    fw::ScriptManager::get()->loadScript(m_scriptId, name, ml::FILE_PRIO(7));
    fw::ScriptManager::get()->getScript(m_scriptId).start();
}

bool GfFieldGmkTutorial::isEnd() const {
    if (m_waitMover) {
        return true;
    }
    const fw::ScriptManager* manager = fw::ScriptManager::get();
    return manager->getScript(m_scriptId).isFinish();
}

void GfFieldGmkTutorial::gevMapjump(GEV ev, const MapjumpCallbackInfo&) {
    if (ev == GEV(1)) {
        dispose();
    }
}

bool AFieldSeq::cancel() {
    dispose();
    return true;
}

void AFieldSeq::onFsFailed() {}

GfFieldMapGimmick::GfFieldMapGimmick(const GfSetupParam& param)
    : AFieldSeq(param), m_camera(nullptr), m_seqCamera(nullptr), m_seqLod(nullptr), m_lodStep(0), m_lodAnim(0),
      m_seqMapObj(nullptr), m_seqOther(nullptr), m_waitTime(0.0f), m_elapsedTime(0.0f), m_seHandle(0),
      m_solveState(0) {}

void GfFieldMapGimmick::seqCamera_waitToLoaded(float) {
    if (m_camera.isLoaded()) {
        m_seqCamera = &GfFieldMapGimmick::seqCamera_waitToEnd;
    }
}

void GfFieldMapGimmick::dispose() {
    clearSe();
    m_seqCamera = nullptr;
    m_seqLod = nullptr;
    m_lodStep = 0;
    m_lodAnim = 0;
    m_seqMapObj = nullptr;
    m_seqOther = nullptr;
    m_camera.dispose();
    AFieldSeq::dispose();
}

void GfFieldMapGimmick::clearSe() {
    for (int i = 0; i < 5; i++) {
        m_se[i].dispose();
    }
    if (m_seHandle != 0) {
        if (mm::mtl::PtrSingleton<fw::SoundManager>::get()->isLoop(m_seHandle)) {
            mm::mtl::PtrSingleton<fw::SoundManager>::get()->stopSe(m_seHandle, 0.0f);
        }
        m_seHandle = 0;
    }
}

bool GfFieldMapGimmick::isEnd() const {
    if (!AFieldSeq::isEnd()) {
        return false;
    }
    return !m_seqCamera && !m_seqLod && !m_seqMapObj && !m_seqOther;
}

void GfFieldMapGimmick::onFsFailed() {
    m_seqCamera = nullptr;
}

void GfFieldMapGimmick::seqCamera_waitToEnd(float) {
    if (m_camera.isEnd()) {
        m_seqCamera = nullptr;
    }
}

void GfFieldMapGimmick::seqLod_waitToElapseTime(float dt) {
    m_elapsedTime += dt;
    if (m_elapsedTime < m_waitTime) {
        return;
    }
    if (m_lodStep <= 4) {
        m_lodStep++;
        m_seqLod = &GfFieldMapGimmick::seqLod_init;
        return;
    }
    m_seqLod = nullptr;
    if (m_bdatInfo.m_nowaitGmkCam && m_isFsSucceeded) {
        if (gmk::GmkMapGimmick* gmk = static_cast<gmk::GmkMapGimmick*>(m_gmkAcc.m_gmk)) {
            SCOM_QUEST_GIMMICK::createMapGimmick(gmk->m_createInfo.m_bdatId, 0.0f);
            gmk->setSolved();
            m_solveState = 2;
        }
    }
}

void GfFieldMapGimmick::seqLod_init(float) {
    gmk::AGmkBase* gmk = m_gmkAcc.m_gmk;
    unsigned char* fp = gmk->getBindedBdatFp();
    int row = gmk->m_createInfo.m_bdatId;
    mm::mtl::FixStr<32> name;
    name.format("G%d_LODmodel", m_lodStep);
    m_lodAnim = (unsigned short)Bdat::getValCheck(fp, name.m_str, row, 2);
    if (m_lodAnim == 0) {
        m_seqLod = nullptr;
        if (m_bdatInfo.m_nowaitGmkCam && m_isFsSucceeded) {
            if (gmk::GmkMapGimmick* gmk = static_cast<gmk::GmkMapGimmick*>(m_gmkAcc.m_gmk)) {
                SCOM_QUEST_GIMMICK::createMapGimmick(gmk->m_createInfo.m_bdatId, 0.0f);
                gmk->setSolved();
                m_solveState = 2;
            }
        }
        return;
    }
    name.format("G%d_LODanime_play", m_lodStep);
    bool reverse = false;
    bool fade = false;
    unsigned int switchId = 1;
    unsigned char mode = (unsigned char)Bdat::getValCheck(fp, name.m_str, row, 1);
    switch (mode) {
    case 0:
        mm::mtl::PtrSingleton<GfFieldLod>::get()->setFade(m_lodAnim, false, false);
        m_seqLod = &GfFieldMapGimmick::seqLod_waitToElapseTime;
        break;
    case 6:
        switchId = 3;
        goto lodSwitch;
    case 5:
        switchId = 2;
    case 4:
    lodSwitch:
        mm::mtl::PtrSingleton<GfFieldLod>::get()->setLodSwitchId(m_lodAnim, switchId);
        m_seqLod = &GfFieldMapGimmick::seqLod_waitToElapseTime;
        break;
    case 2:
        reverse = true;
        goto play;
    case 3:
        fade = true;
    default:
    play:
        if (mm::mtl::PtrSingleton<GfFieldLod>::get()->setAnimReverse(m_lodAnim, reverse, fade)) {
            gmk::applyLodFade(m_lodAnim, fade);
            m_seqLod = &GfFieldMapGimmick::seqLod_waitToEndAnim;
        } else {
            static_cast<gmk::GmkMapGimmick*>(gmk)->validateEffectWithoutLodControl(m_lodAnim, false);
            m_seqLod = &GfFieldMapGimmick::seqLod_waitToElapseTime;
        }
        break;
    }
    name.format("nextwait%d", m_lodStep);
    m_waitTime = (short)Bdat::getValCheck(fp, name.m_str, row, 5);
    m_elapsedTime = 0.0f;
    name.format("G%d_LOD_SE", m_lodStep);
    unsigned short seId = (unsigned short)Bdat::getValCheck(fp, name.m_str, row, 2);
    if (seId) {
        gmk::GmkCtrlVolSe::CreateInfo info;
        name.format("G%d_LOD_SE_type", m_lodStep);
        info.m_pack = Bdat::getFlagVal(fp, "flag", row, name.m_str)
                          ? mm::mtl::PtrSingleton<GfFieldSound>::get()->getMapPack()
                          : mm::mtl::PtrSingleton<GfFieldSound>::get()->getCommonPack();
        name.format("G%d_LOD_size", m_lodStep);
        float size = (unsigned char)Bdat::getValCheck(fp, name.m_str, row, 1);
        info.m_seId = seId;
        info.m_minDist = size;
        info.m_maxDist = size;
        info.m_pos = *gmk->m_pos;
        m_se[m_lodStep - 1].create(info);
    }
}

void GfFieldMapGimmick::seqLod_waitToEndAnim(float) {
    if (mm::mtl::PtrSingleton<GfFieldLod>::get()->isPlayAnimEnd(m_lodAnim)) {
        m_seqLod = &GfFieldMapGimmick::seqLod_waitToElapseTime;
    }
}

void GfFieldMapGimmick::seqMapObj_nextwait(float dt) {
    m_elapsedTime += dt;
    if (m_elapsedTime < m_waitTime) {
        return;
    }
    m_seqMapObj = nullptr;
    if (m_bdatInfo.m_nowaitGmkCam && m_isFsSucceeded) {
        if (gmk::GmkMapGimmick* gmk = static_cast<gmk::GmkMapGimmick*>(m_gmkAcc.m_gmk)) {
            SCOM_QUEST_GIMMICK::createMapGimmick(gmk->m_createInfo.m_bdatId, 0.0f);
            gmk->setSolved();
            m_solveState = 2;
        }
    }
}

void GfFieldMapGimmick::seqEffect_nextwait(float dt) {
    m_elapsedTime += dt;
    if (m_elapsedTime < m_waitTime) {
        return;
    }
    m_seqOther = nullptr;
    if (m_bdatInfo.m_nowaitGmkCam && m_isFsSucceeded) {
        if (gmk::GmkMapGimmick* gmk = static_cast<gmk::GmkMapGimmick*>(m_gmkAcc.m_gmk)) {
            SCOM_QUEST_GIMMICK::createMapGimmick(gmk->m_createInfo.m_bdatId, 0.0f);
            gmk->setSolved();
            m_solveState = 2;
        }
    }
}

void GfFieldMapGimmick::BdatInfo::create(CBdatWrapper bdat, int row) {
    m_opCondition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "OP_Condition", row, 2);
    m_bootedGmk = gmk::BootedGmkCond(bdat, row, "OP_");
    m_scenarioFlag = gmk::ScenarioFlagCond(bdat, row, "OP_");
    m_questFlag = gmk::QuestFlagCond(bdat, row, "OP_");
    m_time.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "OP_Time", row, 2);
    m_weather.m_weather = (unsigned char)Bdat::getValCheck(bdat.m_fp, "OP_weather", row, 1);
    m_camGimAtr = (unsigned char)Bdat::getValCheck(bdat.m_fp, "camGim_ATR", row, 1);
    m_gmkCamPos = Bdat::getFlagVal(bdat.m_fp, "flag", row, "gmkCamPos") != 0;
    m_nowaitGmkCam = Bdat::getFlagVal(bdat.m_fp, "flag", row, "nowaitGmkCam") != 0;
}

bool GfFieldMapGimmick::BdatInfo::isCondMatched() const {
    if (m_opCondition != 0 && !GfGameCond::isGameCond(m_opCondition)) {
        return false;
    }
    if (m_bootedGmk.m_gimmickType != 0 && m_bootedGmk.m_gimmickId != 0 && !m_bootedGmk.isMatch()) {
        return false;
    }
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.m_questFlag != 0 && m_questFlag.m_questFlagMin <= m_questFlag.m_questFlagMax &&
        !m_questFlag.isMatch()) {
        return false;
    }
    if (m_time.m_time != 0 && !m_time.isMatch()) {
        return false;
    }
    if (m_weather.m_weather != 0 && !m_weather.isMatch()) {
        return false;
    }
    return true;
}

void GfFieldMapGimmick::create(GF_OBJ_HANDLE* handle) {
    AFieldSeq::create(handle);
    if (gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle)) {
        unsigned char* fp = gmk->getBindedBdatFp();
        int row = gmk->m_createInfo.m_bdatId;
        m_bdatInfo.create(fp, row);
        GfObj* obj = GfObjUtil::getObj(m_handle);
        if (obj == nullptr || (obj->pad_110 & 4) == 0 || m_bdatInfo.isCondMatched()) {
            {
                gmk::GmkAcc::CreateInfo accInfo;
                accInfo.validate(*gmk);
                m_gmkAcc.create(accInfo);
            }
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "gmkCamName", row, 7));
            if (name == nullptr || name[0] == '\0') {
                return;
            }
            gmk::GmkCamera::CreateInfo camInfo;
            camInfo.m_name = name;
            if (m_bdatInfo.m_camGimAtr != 0) {
                camInfo.m_attr = m_bdatInfo.m_camGimAtr;
            }
            camInfo.pad_105 = false;
            if (m_bdatInfo.m_gmkCamPos) {
                if (m_lodAnim > 0) {
                    camInfo.validateTransform(m_lodAnim);
                } else {
                    camInfo.validateTransform(m_handle);
                }
            }
            m_camera.create(camInfo);
            m_seqCamera = &GfFieldMapGimmick::seqCamera_waitToLoaded;
            return;
        }
        MenuCommonWindowParam param;
        param.m_bdat = GfDataBdat::getFP(0x1b1);
        param.m_msgId = (unsigned short)Bdat::getValCheck(fp, "missMSG_ID", row, 2);
        GfPlayFactory::createCommonMessage(param);
    }
    dispose();
    m_isEnd = true;
}

void GfFieldMapGimmick::update(float dt) {
    if (m_solveState == 1) {
        if (GfGameManager::isGameTypeIra()) {
            if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::get()) {
                scene->setArenaPlayerStop(true);
            }
        }
    } else if (m_solveState == 2) {
        if (GfGameManager::isGameTypeIra()) {
            if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::get()) {
                scene->setArenaPlayerStop(false);
            }
        }
    }
    m_solveState = 0;
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    bool wasEnd = isEnd();
    if (m_camera.m_info.m_name.m_nLen > 0) {
        m_camera.update(dt);
        if (m_seqCamera) {
            (this->*m_seqCamera)(dt);
        }
        if (m_seqCamera == &GfFieldMapGimmick::seqCamera_waitToLoaded) {
            return;
        }
    }
    AFieldSeq::update(dt);
    if (m_seqLod) {
        (this->*m_seqLod)(dt);
    }
    if (m_seqMapObj) {
        (this->*m_seqMapObj)(dt);
    }
    if (m_seqOther) {
        (this->*m_seqOther)(dt);
    }
    if (!wasEnd && isEnd() && m_isFsSucceeded) {
        if (gmk::GmkMapGimmick* gmk = static_cast<gmk::GmkMapGimmick*>(m_gmkAcc.m_gmk)) {
            SCOM_QUEST_GIMMICK::createMapGimmick(gmk->m_createInfo.m_bdatId, 0.0f);
            gmk->setSolved();
            m_solveState = 2;
        }
    }
}

void GfFieldMapGimmick::onFsSucceeded() {
    if (m_camera.m_info.m_name.m_nLen > 0) {
        m_camera.play();
    }
    m_lodStep = 1;
    m_seqLod = &GfFieldMapGimmick::seqLod_init;
    if (GfGameManager::isGameTypeIra() && m_gmkAcc.isValid() &&
        static_cast<gmk::GmkMapGimmick*>(m_gmkAcc.m_gmk)->getBdatInfo()->m_effectId != 0) {
        m_seqOther = &GfFieldMapGimmick::seqEffect_init;
    } else {
        m_seqMapObj = &GfFieldMapGimmick::seqMapObj_init;
    }
    m_solveState = 1;
}

void GfFieldJump::onFsSucceeded() {
    gmk::GmkJump* gmk = static_cast<gmk::GmkJump*>(gmk::getBindedGmkInst(m_handle));
    if (gmk) {
        if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
            obj->pad_110 |= 7;
        }
        GfObj* mover = GfObjUtil::getObj(GfGameManager::getControlMover());
        if (mover) {
            GfObj* obj = GfObjUtil::getObj(m_handle);
            if (obj) {
                switch (gmk->getBdatInfo()->m_type) {
                case 0: {
                    MsgPcFieldNotifyWallJump msg;
                    const gmk::GmkJump::Data* data = gmk->getData();
                    msg.m_pos.x = data->m_pos.x;
                    msg.m_pos.y = data->m_pos.y;
                    msg.m_pos.z = data->m_pos.z;
                    msg.m_bdat = gmk->getBindedBdatFp();
                    msg.m_bdatId = gmk->m_createInfo.m_bdatId;
                    msg.m_gmkId = gmk->m_createInfo.m_bdatId;
                    static_cast<fw::MessageObject*>(mover)->recieveMessage(obj, msg);
                    return;
                }
                case 1: {
                    MsgPcFieldNotifyBigJump msg;
                    const gmk::GmkJump::Data* data = gmk->getData();
                    msg.m_pos.x = data->m_pos.x;
                    msg.m_pos.y = data->m_pos.y;
                    msg.m_pos.z = data->m_pos.z;
                    msg.m_param0 = data->m_param[0];
                    msg.m_param1 = data->m_param[1];
                    msg.m_param2 = data->m_param[2];
                    msg.m_bdat = gmk->getBindedBdatFp();
                    msg.m_bdatId = gmk->m_createInfo.m_bdatId;
                    msg.m_gmkId = gmk->m_createInfo.m_bdatId;
                    static_cast<fw::MessageObject*>(mover)->recieveMessage(obj, msg);
                    if (GfGameManager::isGameTypeIra()) {
                        gmk->onFsSucceeded();
                    }
                    return;
                }
                }
            }
        }
    }
    dispose();
}

void GfFieldWarp::onFsSucceeded() {
    gmk::GmkWarp* gmk = static_cast<gmk::GmkWarp*>(gmk::getBindedGmkInst(m_handle));
    if (gmk) {
        if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
            obj->pad_110 |= 7;
        }
        GfObj* mover = GfObjUtil::getObj(GfGameManager::getControlMover());
        if (mover) {
            GfObj* obj = GfObjUtil::getObj(m_handle);
            if (obj) {
                MsgPcFieldNotifyWarp msg;
                const gmk::GmkWarp::Point* points = gmk->getPoints();
                bool second = m_handle == gmk->m_firstHandle;
                const mm::Vec3NA& pos = second ? points[1].m_pos : points[0].m_pos;
                msg.m_pos.x = pos.x;
                msg.m_pos.y = pos.y;
                msg.m_pos.z = pos.z;
                msg.m_param = second ? points[1].m_param : points[0].m_param;
                msg.m_bdat = gmk->getBindedBdatFp();
                msg.m_bdatId = gmk->m_createInfo.m_bdatId;
                msg.m_gmkId = gmk->m_createInfo.m_bdatId;
                static_cast<fw::MessageObject*>(mover)->recieveMessage(obj, msg);
                return;
            }
        }
    }
    dispose();
}

}  // namespace gf
