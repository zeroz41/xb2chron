#include "classes/gf/GfAppendWire.h"
#include "classes/anm/Skeleton.h"
#include "gf/GfUtil.h"
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

}  // namespace gf
