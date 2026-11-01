#include "classes/gf/GfSound.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/TUnk_B52C38.h"
#include "classes/gf/TUnk_28D5BC.h"
#include "classes/gf/TUnk_28D7B8.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfEvent.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/TUnk_B535D0.h"
#include "classes/gf/TUnk_B607D8.h"
#include "btl/Utility.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataParty.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gmk/TUnk_B6D528.h"
#include "classes/gf/TUnk_B60928.h"
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
#include "gf/GfUtil.h"
#include "ml/ScnObjAccResNode.h"
#include <string.h>

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


bool TUnk_B52C38::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x1000034) {
        fn_710028C9CC(sender, static_cast<MsgUnk_1000034&>(msg));
        return true;
    }
    return false;
}

TUnk_B52C38::~TUnk_B52C38() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void TUnk_B52C38::fn_710028D128() {
    m_isDone = false;
    pad_A8 = 1;
    while (GfGameManager::isFading(-1)) {
        m_owner->fn_7100291E2C(0);
    }
    if (m_context == nullptr) {
        m_context = GfMenuCallContext::create();
        if (m_context == nullptr) {
            return;
        }
    }
    m_context->reset();
    TUnk_B607D8::OpenParam param = {0, 0};
    if (TUnk_B607D8::fn_71003B0CE4(m_context, param)) {
        btl::Utility::fn_710000FB6C();
        while (!m_context->isTerm()) {
            m_owner->fn_7100291E2C(0);
        }
    }
}

void TUnk_B52C38::fn_710028D1CC() {
    pad_7C = 0;
    pad_98 = true;
    m_isDone = false;
    gmk::TUnk_B6D528::s_battleId = m_key.m_id;
    unsigned int mode = GfBdatBtl::get()->fn_71001E98AC(m_key.m_id);
    if (pad_7C == 0) {
        if (mode == 3) {
            do {
                if (m_result == 2 || m_owner->fn_7100291D68()) {
                    break;
                }
                m_owner->fn_7100291E2C(0);
            } while (pad_7C == 0);
        } else {
            do {
                if (m_result == 2 || m_owner->fn_7100291D68()) {
                    break;
                }
                unsigned int wave = gmk::TUnk_B6D528::s_state.m_waveIndex;
                if (pad_A8 != wave) {
                    int result = gmk::TUnk_B6D528::s_state.m_result;
                    if (m_context != nullptr || (m_context = GfMenuCallContext::create()) != nullptr) {
                        m_context->reset();
                        TUnk_B607D8::OpenParam param;
                        param.m_type = wave != 0 ? (result == 1 ? 2 : 1) : 0;
                        param.m_value = wave;
                        if (TUnk_B607D8::fn_71003B0CE4(m_context, param)) {
                            pad_A8 = wave;
                        }
                    }
                }
                m_owner->fn_7100291E2C(0);
            } while (pad_7C == 0);
        }
    }
    while (GfPlayComStartTutorial::s_activateCount > 0) {
        m_owner->fn_7100291E2C(0);
    }
    gmk::TUnk_B6D528::fn_71005B7344();
    pad_98 = false;
    m_isDone = true;
}

void TUnk_B52C38::fn_710028D584() {
    m_owner->m_partySetup->fn_710028E15C();
    memcpy(fn_71002EE8C4(), m_option, sizeof(m_option));
    GfEvent::fn_71003274A8();
}

TUnk_28D5BC::TUnk_28D5BC()
    : m_category(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)), m_delay(0.0f), m_fadeTime(0.0f), m_bgm(0) {}

TUnk_28D5BC::~TUnk_28D5BC() {}

void TUnk_28D5BC::fn_710028D5F0() {
    if (GfSound* sound = GfSound::get()) {
        m_category = sound->createCategoryHandle();
    }
}

void TUnk_28D5BC::fn_710028D624() {
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(m_category);
    }
}

void TUnk_28D5BC::fn_710028D644(const fw::UpdateInfo& info) {
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

TUnk_28D7B8::TUnk_28D7B8(TUnk_B535D0* owner) : m_owner(owner) {}

TUnk_28D7B8::~TUnk_28D7B8() {}


void TUnk_28D7B8::fn_710028DA24() {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    unsigned int start = bdat->getChrBlStart();
    unsigned int end = bdat->getChrBlEnd();
    for (unsigned int blade = start; blade < end; blade++) {
        if (bdat->fn_71001ED40C(blade) && fn_71002EDAD4(blade) && GfDataBlade::isActivateUnuse(blade)) {
            GfDataBlade::setActivateReserver(blade);
            fn_71002FE418(blade);
        }
    }
}

void TUnk_28D7B8::fn_710028DAB4() {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    unsigned int start = bdat->getChrBlStart();
    unsigned int end = bdat->getChrBlEnd();
    for (unsigned int blade = start; blade < end; blade++) {
        if (bdat->fn_71001ED40C(blade) && fn_71002EDAD4(blade) && !GfDataBlade::isActivateUnuse(blade) &&
            !((blade == 0x452 || blade == 0x453) && GfGameManager::fn_71002AC650()) &&
            !(blade == 0x457 && GfGameManager::fn_71002AC670())) {
            GfDataDriver::unsetBlade(blade);
            GfDataBlade::setActivateUnuse(blade);
        }
    }
    fn_71002EC268(false, true);
}

void TUnk_28D7B8::fn_710028DF1C(const GfGameManager::BattleChallengeRecord::Key& key) {
    m_lists.fn_71002907A0(key);
    for (const GfGameManager::BattleChallengeRecord::Entry38& entry : m_lists.m_list38) {
        GfDataDriver::fn_710024487C(entry.m_driver, entry.m_challengeLevel);
    }
    m_owner->m_record.m_lists.m_list38 = m_lists.m_list38;
}

void TUnk_28D7B8::fn_710028E050(const GfGameManager::BattleChallengeRecord::Key& key) {
    m_lists.fn_71002908DC(key);
    m_owner->m_record.m_lists.m_listE0 = m_lists.m_listE0;
}

void TUnk_28D7B8::fn_710028E15C() {
    mm::mtl::FixedVector<unsigned int, 32> blades;
    m_party.getAllBlade(blades);
    for (unsigned int blade : blades) {
        GfDataBlade::setUnselect(blade, false);
    }
    for (const GfGameManager::BattleChallengeRecord::Entry38& entry : m_lists.m_list38) {
        GfDataDriver::fn_710024487C(entry.m_driver, entry.m_level);
    }
    GfGameParty::setupRequestData(m_party);
    m_lists.m_list38.clear();
    m_lists.m_listE0.clear();
    m_owner->m_record.m_lists = m_lists;
}

bool TUnk_28D7B8::fn_710028E3F8(const GfGameManager::BattleChallengeRecord::Key& key) {
    if (key.m_id == 0) {
        return false;
    }
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (bdat->fn_71001E98AC(key.m_id) == 3) {
        return true;
    }
    for (unsigned int slot = 0; slot < 3; slot++) {
        unsigned int driver = bdat->fn_71001EA2D4(key.m_id, slot);
        if (!(driver == 0 || driver == 7 || driver == 9) && !GfDataParty::isExistDriver(driver)) {
            return false;
        }
    }
    return true;
}

}  // namespace gf
