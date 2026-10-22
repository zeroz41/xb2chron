#include "classes/fw/MessageObject.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameParty.h"
#include "fw/NaviUtil.h"
#include "gf/GfParamFormation.h"
#include "gf/MsgPcFieldNotifyChangePlayerID.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "math.h"

namespace gf {

void GfGamePlayerFormation::build(const GfSetupParam& param) {
#line 67
    GfGamePlayerFormation* formation = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGamePlayerFormation();
    formation->setup(param);
}

void GfGamePlayerFormation::destroy() {
    delete get();
}

void GfGamePlayerFormation::update(const fw::UpdateInfo& info) {
    get()->updateImpl(info);
}

void GfGamePlayerFormation::updateImpl(const fw::UpdateInfo& info) {
    m_formation = GfGameParty::isBtlLeaderDirver();
    for (unsigned int i = 0; i < 9; i++) {
        if (GfObj* obj = GfObjUtil::getObj(m_players[i].m_handle)) {
            GfObjAcc acc(obj);
            m_followTransforms[i] = acc.getWorldTransform();
        }
    }
    float sign = m_flip ? -1.0f : 1.0f;
    for (unsigned int i = 0; i < 9; i++) {
        if (m_players[i].m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            continue;
        }
        unsigned int follow = m_players[i].m_followIndex;
        if (i == 0 || follow == static_cast<unsigned int>(-1)) {
            m_targetPos[i] = m_followTransforms[i].position;
            continue;
        }
        const FormationParam* param = getFormationParam(m_formation);
        unsigned int slot = i - 1;
        if (slot > 4) {
            slot = 4;
        }
        const fw::Transform& transform = m_followTransforms[follow];
        mm::Vec3 offset(sign * param->playerOffset[slot].x, 0.0f, param->playerOffset[slot].z);
        mm::Vec3 pos = transform.position + transform.rotation.rotate(offset);
        m_formationPos[i] = pos;
        mm::Vec3 hit;
        if (fw::NaviUtil::testNaviStraightLine(hit, transform.position, pos, 3.0f, 20.0f) != 2) {
            m_targetPos[i] = transform.position;
            if (stopPlayer(i, m_targetPos[i], 1.5f)) {
                m_targetPos[i] = m_followTransforms[i].position;
            }
        } else {
            m_targetPos[i] = pos;
        }
    }
}

GfGamePlayerFormation::~GfGamePlayerFormation() {}

void GfGamePlayerFormation::calcTargetTransform(const fw::Transform& transform, unsigned int index,
                                                mm::Vec3* pOut) const {
    float sign = m_flip ? -1.0f : 1.0f;
    switch (index) {
    case 0:
        *pOut = transform.position;
        break;
    case 1:
    case 2:
    case 4: {
        const FormationParam* param = getFormationParam(m_formation);
        const FormationParam::Offset& offset = param->playerOffset[index - 1];
        *pOut = transform.position + transform.rotation.rotate(mm::Vec3(sign * offset.x, 0.0f, offset.z));
        break;
    }
    case 3:
    case 5: {
        const FormationParam* param = getFormationParam(m_formation);
        const FormationParam::Offset& offset0 = param->playerOffset[index - 1];
        const FormationParam::Offset& offset1 = param->playerOffset[index - 2];
        *pOut = transform.position +
                transform.rotation.rotate(mm::Vec3(sign * (offset0.x + offset1.x), 0.0f, offset0.z + offset1.z));
        break;
    }
    default:
        *pOut = transform.position;
        break;
    }
}

const fw::Transform& GfGamePlayerFormation::getFollowTransform(unsigned int index) const {
    unsigned int follow = m_players[index].m_followIndex;
    if (follow == static_cast<unsigned int>(-1)) {
        follow = index;
    }
    return m_followTransforms[follow];
}

void GfGamePlayerFormation::swapFormation(GF_OBJ_HANDLE* handle0, GF_OBJ_HANDLE* handle1) {
    swapFormation(findPlayer(handle0), findPlayer(handle1));
}

unsigned int GfGamePlayerFormation::findPlayer(GF_OBJ_HANDLE* handle) {
    for (unsigned int i = 0; i < 9; i++) {
        if (m_players[i].m_handle == handle) {
            return i;
        }
    }
    return -1;
}

void GfGamePlayerFormation::swapFormation(unsigned int index0, unsigned int index1) {
    if (index0 == static_cast<unsigned int>(-1) || index1 == static_cast<unsigned int>(-1)) {
        return;
    }
    Player& player0 = m_players[index0];
    Player& player1 = m_players[index1];
    GF_OBJ_HANDLE* handle = player0.m_handle;
    player0.m_handle = player1.m_handle;
    player1.m_handle = handle;
    {
        MsgPcFieldNotifyChangePlayerID msg(index0);
        if (GfObj* obj = GfObjUtil::getObj(player0.m_handle)) {
            sendMessage(obj, msg);
        }
    }
    {
        MsgPcFieldNotifyChangePlayerID msg(index1);
        if (GfObj* obj = GfObjUtil::getObj(player1.m_handle)) {
            sendMessage(obj, msg);
        }
    }
    GfEvent::callSwapFormation(index0, index1);
}

bool GfGamePlayerFormation::isFarRandomTalk(GF_OBJ_HANDLE* handle) {
    unsigned int index = findPlayer(handle);
    if (index == static_cast<unsigned int>(-1)) {
        return false;
    }
    const WarpForRandomTalkParam* param = getWarpForRandomTalkParam();
    mm::Vec3 diff = m_followTransforms[0].position - m_followTransforms[index].position;
    if (::fabsf(diff.y) >= param->distVert) {
        return true;
    }
    float distHorzSq = param->distHorz * param->distHorz;
    return diff.x * diff.x + diff.z * diff.z >= distHorzSq;
}

}  // namespace gf
