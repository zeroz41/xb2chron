#include "classes/gf/GfSound.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfArenaBattle.h"
#include "classes/gf/GfArenaJingle.h"
#include "classes/gf/GfArenaParty.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfEvent.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameArena.h"
#include "gf/GfArenaUtil.h"
#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "btl/Utility.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataParty.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gmk/GmkBattleChallenge.h"
#include "classes/gf/GfMenuObjBtlTime.h"
#include "classes/gf/GfAppendWire.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/ModelObject.h"
#include "classes/gf/GfComModel.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/Transform.h"
#include "fw/UpdateInfo.h"
#include "gf/GfDataDriver.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfUtil.h"
#include "ml/ScnObjAccResNode.h"
#include <string.h>
#include "gf/GfGameUtilDiff.h"
#include "gf/GfGameUtil.h"
#include "gf/GfKizunaringBlade.h"

namespace gf {

GfAppendWire::GfAppendWire(GF_OBJ_HANDLE* owner, GF_OBJ_HANDLE* wire)
    : m_owner(owner),
      m_wire(wire),
      m_ownerMountBone(0xFFFF),
      m_wireBoneA(0xFFFF),
      m_wireBoneB(0xFFFF),
      m_wireAccBoneA(0xFFFF),
      m_target(reinterpret_cast<GF_OBJ_HANDLE*>(-1)),
      m_targetPos(mm::Vec3::zero),
      m_targetBone(-1),
      m_state(STATE_NONE),
      m_timer(0.0f),
      m_time(0.0f),
      m_holdTime(0.0f),
      m_closeTime(0.0f),
      m_salvagePoint(false) {
    if (GfComModel* model = GfObjUtil::getComModel(m_wire)) {
        ml::ScnObjAccResNode node(model->m_model->getInterface());
        m_wireBoneA = node.getBoneIndex(GfDataDriver::getBelongingMountBoneA());
        m_wireBoneB = node.getBoneIndex(GfDataDriver::getBelongingMountBoneB());
    }
    m_wireAccBoneA = GfObjAcc(m_wire).getBoneIdx(GfDataDriver::getBelongingMountBoneA());

    const anm::Skeleton* skeleton = GfObjUtil::getComModel(m_owner)->m_skeleton;
    if (skeleton != nullptr) {
        for (unsigned int i = 0, count = skeleton->m_mountNames.size(); i < count; i++) {
            if (strcmp(skeleton->m_mountNames[static_cast<unsigned short>(i)],
                       GfDataDriver::getBelongingMountBone()) == 0) {
                m_ownerMountBone = i;
                break;
            }
        }
    }
    resetWire();
}

void GfAppendWire::endWire(float time) {
    if (time <= 0.0f) {
        resetWire();
    } else {
        m_state = STATE_RETRACT;
        m_time = time;
        m_target = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
}

GfAppendWire::~GfAppendWire() {}

void GfAppendWire::startWire(GF_OBJ_HANDLE* target, float time) {
    startWireWithClose(target, time, 0.0f, 0.0f);
}

void GfAppendWire::startWireWithClose(GF_OBJ_HANDLE* target, float time, float holdTime, float closeTime) {
    endWire(0.0f);
    if (m_state == STATE_NONE) {
        GfObjAcc wire(m_wire);
        wire.setAlphaNormal(1.0f);
    }
    m_state = STATE_EXTEND;
    m_target = target;
    m_time = time;
    m_timer = 0.0f;
    {
        GfObjAcc acc(target);
        m_targetBone = acc.getBoneIdx("JD_hip");
        if (m_targetBone < 0) {
            m_targetBone = acc.getBoneIdx("JD_hipA");
        }
    }
    m_holdTime = holdTime;
    m_closeTime = closeTime;
    checkAndSetupSalvagePoint();
}

void GfAppendWire::checkAndSetupSalvagePoint() {
    GfObjAcc target(m_target);
    // type 8 objects bound to gimmick type 0x1F: salvage points (inferred from the function's name)
    if (target.getType() == 8) {
        gmk::AGmkBase* gimmick = gmk::getBindedGmkInst(m_target);
        if (gimmick != nullptr && gimmick->getGmkType() == static_cast<gmk::GmkType>(0x1F)) {
            mm::Vec3 forward = target.getWorldTransform().rotation.rotate(mm::Vec3(0.0f, 0.0f, 2.0f));
            mm::Vec3 front = target.getWorldTransform().position + forward;
            m_targetPos = target.getWorldTransform().position;
            mm::Vec3 dir = front - m_targetPos;
            float length = dir.length();
            if (length <= 1e-6f) {
                dir = mm::Vec3::zero;
            } else {
                float scale = 1.0f / length;
                dir.x *= scale;
                dir.y *= scale;
                dir.z *= scale;
            }
            mm::Vec3 step = dir * 0.1f;
            mm::Vec3 pos = m_targetPos;
            for (unsigned int i = 1; i < 21; i++) {
                pos = step + pos;
                mm::Vec3 from = pos + mm::Vec3(0.0f, 1.0f, 0.0f);
                mm::Vec3 to = pos + mm::Vec3(0.0f, -0.8f, 0.0f);
                mm::Vec3 hit;
                if (!util::getHitCollision(hit, from, to)) {
                    break;
                }
                m_targetPos = hit + mm::Vec3(0.0f, -0.1f, 0.0f);
            }
            m_salvagePoint = true;
        }
    }
}

void GfAppendWire::calcTargetPosotion() {
    GfObjAcc target(m_target);
    if (target.getObj() == nullptr) {
        endWire(m_time);
    } else if (!m_salvagePoint) {
        if (target.isValidModel()) {
            fw::Transform bone;
            if (target.getBoneTransform(bone, m_targetBone)) {
                m_targetPos = bone.position;
                return;
            }
            m_targetPos = target.getWorldTransform().position + mm::Vec3(0.0f, 0.4f, 0.0f);
        } else {
            m_targetPos = target.getWorldTransform().position + mm::Vec3(0.0f, -0.2f, 0.0f);
        }
    }
}

void GfAppendWire::updateState(const fw::UpdateInfo& info) {
    switch (m_state) {
    case STATE_EXTEND:
        calcTargetPosotion();
        m_timer += info.m_deltaTime;
        if (m_timer >= m_time) {
            m_timer = m_time;
            if (m_holdTime > 0.0f) {
                m_state = STATE_HOLD;
            }
        }
        break;
    case STATE_HOLD:
        calcTargetPosotion();
        m_holdTime -= info.m_deltaTime;
        if (m_holdTime <= 0.0f) {
            m_holdTime = 0.0f;
            if (m_closeTime <= 0.0f) {
                resetWire();
                m_closeTime = 0.0f;
            } else {
                m_state = STATE_RETRACT;
                m_time = m_closeTime;
                m_closeTime = 0.0f;
                m_target = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            }
        }
        break;
    case STATE_RETRACT:
        m_timer -= info.m_deltaTime;
        if (m_timer <= 0.0f) {
            resetWire();
        }
        break;
    }
}


bool GfArenaBattle::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x1000034) {
        procMsgGameBtlArena(sender, static_cast<MsgGameBtlArena&>(msg));
        return true;
    }
    return false;
}

GfArenaBattle::~GfArenaBattle() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfArenaBattle::execBattleStart(fw::UpdateInfo const&) {
    m_isDone = false;
    pad_A8 = 1;
    while (GfGameManager::isFading(-1)) {
        m_owner->sleep(0);
    }
    if (m_context == nullptr) {
        m_context = GfMenuCallContext::create();
        if (m_context == nullptr) {
            return;
        }
    }
    m_context->reset();
    GfMenuObjBtlchTelop::OpenParam param = {0, 0};
    if (GfMenuObjBtlchTelop::open(m_context, param)) {
        btl::Utility::ChallengeBattleStartTelopCallback();
        while (!m_context->isTerm()) {
            m_owner->sleep(0);
        }
    }
}

void GfArenaBattle::execBattle(fw::UpdateInfo const&) {
    pad_7C = 0;
    pad_98 = true;
    m_isDone = false;
    gmk::GmkBattleChallenge::sm_targetGmkBdatId = m_key.m_id;
    unsigned int mode = GfBdatBtl::get()->getBTL_ChBtlType(m_key.m_id);
    if (pad_7C == 0) {
        if (mode == 3) {
            do {
                if (m_result == 2 || m_owner->isDestroyNow()) {
                    break;
                }
                m_owner->sleep(0);
            } while (pad_7C == 0);
        } else {
            do {
                if (m_result == 2 || m_owner->isDestroyNow()) {
                    break;
                }
                unsigned int wave = gmk::GmkBattleChallenge::sm_battleStatus.m_waveIndex;
                if (pad_A8 != wave) {
                    int result = gmk::GmkBattleChallenge::sm_battleStatus.m_result;
                    if (m_context != nullptr || (m_context = GfMenuCallContext::create()) != nullptr) {
                        m_context->reset();
                        GfMenuObjBtlchTelop::OpenParam param;
                        param.m_type = wave != 0 ? (result == 1 ? 2 : 1) : 0;
                        param.m_value = wave;
                        if (GfMenuObjBtlchTelop::open(m_context, param)) {
                            pad_A8 = wave;
                        }
                    }
                }
                m_owner->sleep(0);
            } while (pad_7C == 0);
        }
    }
    while (GfPlayComStartTutorial::s_activateCount > 0) {
        m_owner->sleep(0);
    }
    gmk::GmkBattleChallenge::terminate();
    pad_98 = false;
    m_isDone = true;
}

void GfArenaBattle::mapjumpForReturnFieldForObjCleanup() {
    m_owner->m_partySetup->setupLevelForBattleEnd();
    memcpy(GfGameUtilDiff::getUseSoundUiOption(), m_option, sizeof(m_option));
    GfEvent::callChangeGameDifficult();
}

GfArenaJingle::GfArenaJingle()
    : m_category(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)), m_delay(0.0f), m_fadeTime(0.0f), m_bgm(0) {}

GfArenaJingle::~GfArenaJingle() {}

void GfArenaJingle::initialize() {
    if (GfSound* sound = GfSound::get()) {
        m_category = sound->createCategoryHandle();
    }
}

void GfArenaJingle::finalize() {
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(m_category);
    }
}

void GfArenaJingle::update(const fw::UpdateInfo& info) {
    GfSound* sound = GfSound::get();
    if (sound == nullptr) {
        return;
    }
    if (m_delay > 0.0f) {
        m_delay -= info.m_deltaTime;
        if (m_delay <= 0.0f) {
            m_delay = 0.0f;
            m_handle = sound->playBgm(m_bgm, m_fadeTime, false, 0, static_cast<fw::SoundCategory>(3));
            m_fadeTime = 0.0f;
            m_bgm = 0;
        }
    }
    if (m_handle.isValid() && !sound->isPlaying(m_handle)) {
        stop();
    }
}

GfArenaParty::GfArenaParty(GfGameArena* owner) : m_owner(owner) {}

GfArenaParty::~GfArenaParty() {}


void GfArenaParty::addFieldBlade() {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    unsigned int start = bdat->getChrBlStart();
    unsigned int end = bdat->getChrBlEnd();
    for (unsigned int blade = start; blade < end; blade++) {
        if (bdat->isChrBlFlagOnlyChBtl(blade) && GfGameUtil::isEnableGameBlade(blade) && GfDataBlade::isActivateUnuse(blade)) {
            GfDataBlade::setActivateReserver(blade);
            GfKizunaringBlade::refreshAchievementCount(blade);
        }
    }
}

void GfArenaParty::removeFieldBlade() {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    unsigned int start = bdat->getChrBlStart();
    unsigned int end = bdat->getChrBlEnd();
    for (unsigned int blade = start; blade < end; blade++) {
        if (bdat->isChrBlFlagOnlyChBtl(blade) && GfGameUtil::isEnableGameBlade(blade) && !GfDataBlade::isActivateUnuse(blade) &&
            !((blade == 0x452 || blade == 0x453) && GfGameManager::isEnableInGameSF()) &&
            !(blade == 0x457 && GfGameManager::isEnableInGameElma())) {
            GfDataDriver::unsetBlade(blade);
            GfDataBlade::setActivateUnuse(blade);
        }
    }
    GfGameUtil::execPartyBladeFollow(false, true);
}

void GfArenaParty::setupLevelForBattleStart(const ArenaBattleStart& key) {
    GfArenaUtil::setupLevelForBattleStart(m_lists, key);
    for (const ArenaChanged::Entry38& entry : m_lists.m_list38) {
        GfDataDriver::setLevel(entry.m_driver, entry.m_challengeLevel);
    }
    m_owner->m_record.m_lists.m_list38 = m_lists.m_list38;
}

void GfArenaParty::setupWeaponParamForBattleStart(const ArenaBattleStart& key) {
    GfArenaUtil::setupRankForBattleStart(m_lists, key);
    m_owner->m_record.m_lists.m_listE0 = m_lists.m_listE0;
}

void GfArenaParty::setupLevelForBattleEnd() {
    mm::mtl::FixedVector<unsigned int, 32> blades;
    m_party.getAllBlade(blades);
    for (unsigned int blade : blades) {
        GfDataBlade::setUnselect(blade, false);
    }
    for (const ArenaChanged::Entry38& entry : m_lists.m_list38) {
        GfDataDriver::setLevel(entry.m_driver, entry.m_level);
    }
    GfGameParty::setupRequestData(m_party);
    m_lists.m_list38.clear();
    m_lists.m_listE0.clear();
    m_owner->m_record.m_lists = m_lists;
}

bool GfArenaParty::checkDriver(const ArenaBattleStart& key) {
    if (key.m_id == 0) {
        return false;
    }
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (bdat->getBTL_ChBtlType(key.m_id) == 3) {
        return true;
    }
    for (unsigned int slot = 0; slot < 3; slot++) {
        unsigned int driver = bdat->getBTL_ChBtlDriver(key.m_id, slot);
        if (!(driver == 0 || driver == 7 || driver == 9) && !GfDataParty::isExistDriver(driver)) {
            return false;
        }
    }
    return true;
}

unsigned int GfArenaParty::getWeaponDamage(const ArenaBattleStart& key, GF_OBJ_HANDLE* handle) const {
    DataParamAcc acc(handle);
    return GfArenaUtil::getWeaponDamage(key, acc.getBlade(-1, false));
}

}  // namespace gf
