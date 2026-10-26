#include "classes/fw/AnimPoseModifier.h"
#include "classes/fw/AnimVolumeFadeModifier.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComModel/ViewerListener.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "classes/gf/mob/StateApproachPc.h"
#include "classes/gf/mob/StateIdle.h"
#include "classes/gf/mob/StateMove.h"
#include "classes/gf/mob/StateSquadMember.h"
#include "gf/GfExecSchedule.h"
#include "classes/gf/GfObj.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/fw/ModelObject.h"
#include "gf/GfObjUtil.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"

namespace gf {
namespace mob {

void StateApproachPc::fn_71004D70EC(GfComBehaviorMob* owner, ai::State*) {
    owner->pad_53d9 = true;
    m_seq = &StateApproachPc::fn_71004D7108;
}

void StateApproachPc::fn_71004D714C(GfComBehaviorMob*, ai::State*) { m_seq = nullptr; }

void StateApproachPc::fn_71004D7154(GfComBehaviorMob* owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateIdle::leave(GfComBehaviorMob* owner, ai::State*) { execEndSchedule(*owner); }

void StateSquadMember::leave(GfComBehaviorMob*, ai::State*) {}

bool StateSquadMember::isCondMatch(const GfComBehaviorMob& owner) { return owner.isSquadMember(); }

void StateMove::leave(GfComBehaviorMob*, ai::State*) {}

bool StateMove::isCondMatch(const GfComBehaviorMob& owner) { return owner.pad_b8 != nullptr; }

}  // namespace mob

bool GfComModel::recieveMessage(fw::MessageObject*, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x01000003:
    case 0x0100003A:
    case 0x0100003B:
        return true;
    }
    return false;
}

GfComModel::GfComModel()
    : pad_10(-1), m_model(nullptr), m_skeleton(nullptr), m_pose(nullptr), m_extraTruckBuffer(nullptr), m_scale(1.0f),
      m_pViewer(nullptr) {
    m_viewerListener.m_pOwner = this;
}

bool GfComModel::isVolumeFadeForUser() const { return GfObjUtil::isVolumeFadeForUser(static_cast<GfObj*>(m_owner)->m_handle); }

bool GfComModel::isRender() const {
    if (m_model != nullptr) {
        return m_model->isRender();
    }
    return false;
}

void GfComModel::setModelScale(float scale) {
    m_scale = scale;
    if (m_model != nullptr) {
        m_model->setScale(scale);
    }
}

void GfComModel::ViewerListener::onWkStandbyLogout() {
    if (m_pOwner != nullptr) {
        m_pOwner->m_pViewer = nullptr;
    }
}

mm::mtl::RTTI GfComModel::m_rtti("GfComModel", &GfComponent::m_rtti, nullptr);

}  // namespace gf
