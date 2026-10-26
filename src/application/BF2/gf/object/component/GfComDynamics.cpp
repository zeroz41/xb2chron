#include "classes/anm/ReferenceObject.h"
#include "classes/skd/CollisionObject.h"
#include "classes/skd/Dynamics.h"
#include "classes/skd/ResDynamics.h"
#include "skd/Factory.h"
#include "classes/fw/ForceCalculator.h"
#include "classes/fw/WindForceCalculator.h"
#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DyanmicsManager.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComDynamics.h"
#include "classes/gf/GfComDynamics/ViewerListener.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/WindProbe.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComWind.h"
#include "fw/Message.h"

namespace gf {

// 1.0.0 handed this message to procMsgActivateComponentDebugWindow, whose body was empty
bool GfComDynamics::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    return msg.m_id == 0x1000003;
}

GfComDynamics::GfComDynamics() : m_level(6), m_forceHighLevel(false), m_pViewer(nullptr) {
    m_viewerListener.m_pOwner = this;  // in the body: the original stores it with m_pViewer, after the table
}

GfComDynamics::~GfComDynamics() {
    ;  // the original stores the table: clang skips the store for an empty body
}

void GfComDynamics::setup(const SetupInfo& info) {
    if (info.res == nullptr) {
        return;
    }
    GfComModel* model = m_owner->getComponent<GfComModel>(1);
    if (model == nullptr) {
        return;
    }
    anm::Pose* pose = model->m_pose;
    if (pose == nullptr) {
        return;
    }

    skd::CollisionObject* colObj = info.colObj;
    bool ownColObj = false;
    if (colObj == nullptr) {
        colObj = skd::Factory::createColObject(info.res->m_pCollisions, *pose, getAllocator(ALLOCATOR(0)));
        ownColObj = true;
    }

    if (info.force) {
        m_force = info.force;
    } else if (GfComWind* wind = m_owner->getComponent<GfComWind>(9)) {
        m_force = fw::WindForceCalculator::create().get();
        fw::WindProbe* probe = wind->m_probe;
        fw::ForceCalculator* force = m_force.operator->();
        fw::WindForceCalculator* windForce = force != nullptr && force->getRTTI()->isKindOf(&fw::WindForceCalculator::m_rtti)
                                                 ? static_cast<fw::WindForceCalculator*>(force)
                                                 : nullptr;
        windForce->bindProbe(*probe);
    }

    skd::Dynamics* dynamics =
        skd::Factory::createDynamics(colObj, *info.res->m_pSolvers, *pose, m_force.get(), getAllocator(ALLOCATOR(0)));
    dynamics->m_packet.m_level = info.level;

    if (fw::DyanmicsManager* manager = fw::DyanmicsManager::get()) {
        unsigned int layer = getLayer();
        m_updater.bind(dynamics, model->m_frame);
        m_updater.m_callback.set(this, &GfComDynamics::applyAttribute);
        manager->addUpdater(layer, m_updater);
        if (dynamics != nullptr) {
            dynamics->release();
        }
        if (ownColObj) {
            m_colUpdater.bind(colObj);
            manager->addColUpdater(layer, m_colUpdater);
            if (colObj != nullptr) {
                colObj->release();
            }
        }
    }
    m_level = info.level;
}

void GfComDynamics::applyAttribute() {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    skd::Dynamics* dynamics = m_updater.m_pDynamics;
    unsigned long attribute = asmCom->getAttribute(AsmCategory(0), AnimLayer(0));
    if (attribute & 4) {
        dynamics->m_paramA = 0.03f;
        dynamics->m_paramB = 0.1f;
    } else {
        dynamics->m_paramA = 0.1f;
        dynamics->m_paramB = 0.0f;
    }
    dynamics->m_packet.m_level = (attribute & 0x40) != 0 || m_forceHighLevel ? 30 : m_level;
}

void GfComDynamics::cleanup() {
    if (fw::ForceCalculator* force = m_force.get()) {
        if (force->getRTTI()->isKindOf(&fw::WindForceCalculator::m_rtti)) {
            static_cast<fw::WindForceCalculator*>(force)->unbindProbe();
        }
    }
    fw::DyanmicsManager* manager = fw::DyanmicsManager::get();
    if (manager == nullptr) {
        return;
    }
    unsigned int layer = getLayer();
    if (m_updater.m_pDynamics != nullptr && m_updater.m_frame.get() != nullptr) {
        manager->removeUpdater(layer, m_updater);
        m_updater.m_callback.m_invoker = nullptr;
        m_updater.unbind();
    }
    if (m_colUpdater.m_pColObj != nullptr) {
        manager->removeColUpdater(layer, m_colUpdater);
        m_colUpdater.unbind();
    }
}

void GfComDynamics::changeLayer(unsigned int from, unsigned int to) {
    fw::DyanmicsManager* manager = fw::DyanmicsManager::get();
    if (manager == nullptr) {
        return;
    }
    if (m_updater.m_pDynamics != nullptr && m_updater.m_frame.get() != nullptr) {
        manager->removeUpdater(from, m_updater);
        manager->addUpdater(to, m_updater);
    }
    if (m_colUpdater.m_pColObj != nullptr) {
        manager->removeColUpdater(from, m_colUpdater);
        manager->addColUpdater(to, m_colUpdater);
    }
}

void GfComDynamics::resetMovement() {
    m_updater.setEnableMovement(false);
    m_updater.setEnableMovement(true);
}

unsigned int GfComDynamics::getSolverCount() const {
    if (m_updater.m_pDynamics != nullptr) {
        return m_updater.m_pDynamics->m_solvers.size();
    }
    return 0;
}

void GfComDynamics::setSolverBlendWeight(unsigned int index, float weight) {
    if (m_updater.m_pDynamics != nullptr) {
        m_updater.m_pDynamics->setSolverBlendWeight(index, weight);
    }
}

void GfComDynamics::ViewerListener::onWkStandbyLogout() {
    if (m_pOwner != nullptr) {
        m_pOwner->m_pViewer = nullptr;
    }
}

mm::mtl::RTTI GfComDynamics::m_rtti("GfComDynamics", &GfComponent::m_rtti, nullptr);

}  // namespace gf
