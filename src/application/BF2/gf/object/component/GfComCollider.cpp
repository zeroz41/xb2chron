#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiUserData.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/AnimAfterModifierInterface.h"
#include "classes/fw/AnimColPoseModifier.h"
#include "classes/fw/AnimationManager.h"
#include "fw/ColiCharacterInfo.h"
#include "classes/gf/GfComCollider.h"
#include "gf/MsgUnk_100003F.h"
#include "gf/MsgUnk_1000040.h"
#include "gf/MsgUnk_1000041.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf {

GfComCollider::GfComCollider() : m_coliObjects(getAllocator(ALLOCATOR(0))), m_userData(nullptr) {
    m_userData.m_owner = this;  // in the body: the original stores it after the pose modifier's constructor
}

GfComCollider::~GfComCollider() {
    ;  // the original stores the tables: clang skips the stores for an empty body
}

void GfComCollider::setup(const SetupInfo& info) {
    m_coliObjects.resize(2, nullptr);
}

void GfComCollider::cleanup() {
    if (m_poseModifier.isBound()) {
        if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
            manager->removeAfterModifier(getLayer(), m_poseModifier);
        }
        m_poseModifier.unbind();
    }
    for (unsigned int i = 0; i < m_coliObjects.size(); ++i) {
        if (fw::ColiObject* coli = m_coliObjects[i]) {
            coli->m_eventMask = 0;
            coli->m_listener = nullptr;
            coli->m_userData = nullptr;
        }
        if (m_coliObjects[i] != nullptr) {
            m_coliObjects[i]->release();
            m_coliObjects[i] = nullptr;
        }
    }
    m_coliObjects.clear();
}

void GfComCollider::createColiCharacter(unsigned int index, const fw::ColiCharacterInfo& info,
                                        mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
    createColi(&fw::ColiObject::createColiCharacter, index, info, frame);
}

template <typename Info, typename Create>
void GfComCollider::createColi(const Create& create, unsigned int index, const Info& info,
                               mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> target = frame;
    if (target.get() == nullptr) {
        target = m_owner->getComponent<GfComTransform>(0)->getFrame();
    }
    m_coliObjects[index] = create(info, target);
    unsigned int mask = info.m_eventMask;
    fw::IColiEventListener* listener = this;
    fw::ColiObject* coli = m_coliObjects[index];
    coli->m_eventMask = mask;
    coli->m_listener = listener;
    m_coliObjects[index]->setUserData(&m_userData);
    if (info.m_shape != nullptr && *info.m_shape == 5) {
        if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
            m_poseModifier.bind(model->m_model, m_coliObjects[index], getAllocator(ALLOCATOR(0)));
            if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
                manager->addAfterModifier(getLayer(), m_poseModifier);
            }
        }
    }
}

void GfComCollider::createColiMoveCharacter(unsigned int index, const fw::ColiCharacterInfo& info,
                                            mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
    createColi(&fw::ColiMoveObject::createColiCharacter, index, info, frame);
}

void GfComCollider::enter(const fw::IColiEventListener::EnterInfo& info) {
    fw::ColiUserData* userData = info.m_other->m_userData;
    if (userData != nullptr && userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
        MsgUnk_100003F msg;
        msg.m_other = static_cast<GfObj*>(static_cast<UserData*>(userData)->m_owner->m_owner)->m_handle;
        msg.m_info = &info;
        GfObj* obj = static_cast<GfObj*>(m_owner);
        obj->sendMessage(obj, msg);
    }
}

void GfComCollider::leave(const fw::IColiEventListener::LeaveInfo& info) {
    fw::ColiUserData* userData = info.m_other->m_userData;
    if (userData != nullptr && userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
        MsgUnk_1000040 msg;
        msg.m_other = static_cast<GfObj*>(static_cast<UserData*>(userData)->m_owner->m_owner)->m_handle;
        msg.m_info = &info;
        GfObj* obj = static_cast<GfObj*>(m_owner);
        obj->sendMessage(obj, msg);
    }
}

void GfComCollider::contact(const fw::IColiEventListener::EnterInfo& info) {
    fw::ColiUserData* userData = info.m_other->m_userData;
    if (userData != nullptr && userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
        MsgUnk_1000041 msg;
        msg.m_other = static_cast<GfObj*>(static_cast<UserData*>(userData)->m_owner->m_owner)->m_handle;
        msg.m_info = &info;
        GfObj* obj = static_cast<GfObj*>(m_owner);
        obj->sendMessage(obj, msg);
    }
}

void GfComCollider::changeLayer(unsigned int, unsigned int) {}

const mm::mtl::RTTI* GfComCollider::UserData::getRTTI() const {
    return &m_rtti;
}

mm::mtl::RTTI GfComCollider::m_rtti("GfComCollider", &GfComponent::m_rtti, nullptr);
mm::mtl::RTTI GfComCollider::UserData::m_rtti("GfComCollider::UserData", &fw::ColiUserData::m_rtti, nullptr);

}  // namespace gf
