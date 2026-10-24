#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/EffectPoint.h"
#include "classes/fw/EffectCasterBase.h"
#include "classes/fw/EffectManager.h"
#include "classes/anm/Pose.h"
#include "classes/skd/CollisionObject.h"
#include "classes/skd/Dynamics.h"
#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DyanmicsManager.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Queue.h"
#include "anm/JobQueue.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/ThreadPool.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Allocator.h"
#include "classes/fw/Framework.h"
#include "fw/UpdateInfo.h"
#include "string.h"

namespace fw {

DynamicsUpdater::DynamicsUpdater()
    : m_pDynamics(nullptr), m_enable(true), m_enableMovement(true), m_resetRequest(false), m_timeScale(1.0f),
      m_pDrawer(nullptr) {
    m_transform.position = mm::Vec3::zero;
    m_transform.rotation = mm::Quat::identity;
    m_prevTransform.position = mm::Vec3::zero;
    m_prevTransform.rotation = mm::Quat::identity;
}

DynamicsUpdater::~DynamicsUpdater() {
    unbind();
}

void DynamicsUpdater::unbind() {
    if (m_pDynamics != nullptr) {
        m_pDynamics->release();
        m_pDynamics = nullptr;
    }
    m_frame = nullptr;
}

inline void DynamicsUpdater::copyFrameTransform() {
    if (m_frame.get() != nullptr) {
        m_transform = m_frame.get()->getWorldTransform();
    }
}

void DynamicsUpdater::bind(skd::Dynamics* dynamics, mm::mtl::IntrusivePtr<ReferenceFrame> frame) {
    unbind();
    m_pDynamics = dynamics;
    dynamics->addRef();
    m_frame = frame;
    copyFrameTransform();
}

void DynamicsUpdater::setEnableMovement(bool enable) {
    if (enable != m_enableMovement) {
        m_enableMovement = enable;
        if (enable) {
            copyFrameTransform();
        }
    }
}

void DynamicsUpdater::update(const UpdateInfo& info) {
    if (m_enable) {
        if (m_callback.isValid()) {
            m_callback();
        }
        if (m_resetRequest) {
            m_pDynamics->resetDynamics();
            m_resetRequest = false;
        } else if (m_enableMovement) {
            const Transform& transform = m_frame->getWorldTransform();
            m_pDynamics->notifyMovement(transform.position, transform.rotation,
                                        m_transform.position + m_prevTransform.position,
                                        m_transform.rotation * m_prevTransform.rotation);
            m_transform = transform;
        }
        m_pDynamics->update(info.m_deltaTime * m_timeScale);
        anm::Pose* pose = m_pDynamics->m_pPose;
        pose->syncLocalSpace();
        pose->syncModelSpace();
    }
}

DynamicsColObjUpdater::DynamicsColObjUpdater() : m_pColObj(nullptr) {}

DynamicsColObjUpdater::~DynamicsColObjUpdater() {
    unbind();
}

void DynamicsColObjUpdater::unbind() {
    if (m_pColObj != nullptr) {
        m_pColObj->release();
        m_pColObj = nullptr;
    }
}

void DynamicsColObjUpdater::bind(skd::CollisionObject* colObj) {
    unbind();
    m_pColObj = colObj;
    colObj->addRef();
}

void DynamicsColObjUpdater::update() {
    m_pColObj->update();
}

mm::mtl::FixedVector<EffectCasterBase*, 256> EffectCasterBase::s_casterList;

void EffectCasterBase::tail() {
    mm::mtl::FixedVector<EffectCasterBase*, 256> list;
    for (unsigned int i = 0; i < s_casterList.size(); i++) {
        if (s_casterList[i]->m_isDead) {
            list.push_back(s_casterList[i]);
        }
    }
    for (unsigned int i = 0; i < list.size(); i++) {
        if (list[i] != nullptr) {
            delete list[i];
            list[i] = nullptr;
        }
    }
}

EffectCasterBase::EffectCasterBase(const EffectPoint* point, unsigned int layer)
    : pad_18(nullptr), pad_20(nullptr), pad_28(0), m_isDead(false) {
    if (this != nullptr && mm::mtl::PtrSingleton<EffectManager>::sys() != nullptr) {
        m_pointCount = 1;
        m_pPoint = nullptr;
        if (point != nullptr) {
            m_pPoint = const_cast<EffectPoint*>(point);
            m_pointCount += point->getPointCount();
            m_pPoint->addRef();
        }
        pad_8 = nullptr;
        m_layer = layer;
        m_pAllocator = Framework::getAllocator();
        mm::mtl::PtrSingleton<EffectManager>::sys()->addCaster(this);
    }
    s_casterList.push_back(this);
}

EffectCasterBase::~EffectCasterBase() {
    if (m_pPoint != nullptr) {
        m_pPoint->release();
        m_pPoint = nullptr;
    }
    mm::mtl::PtrSingleton<EffectManager>::sys()->remove(this);
    mm::mtl::PtrSingleton<EffectManager>::sys()->removeCaster(this);
    for (EffectCasterBase** it = s_casterList.begin(); it != s_casterList.end();) {
        if (*it == this) {
            it = s_casterList.erase(it);
        } else {
            ++it;
        }
    }
}

void EffectCasterBase::setScl(float scl) {
    mm::mtl::PtrSingleton<EffectManager>::get()->sendCaster(this, scl);
}

void EffectCasterBase::setMotionFrame(float frame) {
    mm::mtl::PtrSingleton<EffectManager>::get()->sendCasterFrame(this, frame);
}

void EffectCasterBase::setStateName(const char* name) {
    mm::mtl::PtrSingleton<EffectManager>::get()->sendCasterStateName(this, name);
}

void EffectCasterBase::setEfpMat(mm::Mat44& mtx, const char* name, int index) {
    mm::mtl::PtrSingleton<EffectManager>::get()->sendCaster(this, mtx, name, index);
}

void EffectCasterBase::changeLayer(unsigned int index, unsigned int layer) {
    if (m_layer != layer && m_pPoint != nullptr) {
        m_layer = layer;
        mm::mtl::PtrSingleton<EffectManager>::get()->changeLayerCaster(this, index, layer);
        m_pPoint->m_layer = layer;
    }
}

}  // namespace fw
