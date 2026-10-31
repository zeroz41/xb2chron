#include "classes/fw/DyanmicsManager.h"
#include "classes/fw/WindForceCalculator.h"
#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/WindProbe.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/skd/DynamicsSolver.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/WindProbe.h"
#include "mm/Quat.h"

namespace fw {

const char* DynamicsColUpdateJob::_TYPE_NAME = "DynamicsColUpdateJob";
const char* DynamicsUpdateJob::_TYPE_NAME = "DynamicsUpdateJob";

DynamicsColUpdateJob::DynamicsColUpdateJob(unsigned int count)
    : anm::Job(_TYPE_NAME, sizeof(DynamicsColUpdateJob), 0), m_count(count) {}

void DynamicsColUpdateJob::exec(anm::Job& job) {
    DynamicsColUpdateJob& self = static_cast<DynamicsColUpdateJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_updaters[i]->update();
    }
}

DynamicsUpdateJob::DynamicsUpdateJob(unsigned int count)
    : anm::Job(_TYPE_NAME, sizeof(DynamicsUpdateJob), 1), m_count(count), m_info(nullptr) {}

void DynamicsUpdateJob::exec(anm::Job& job) {
    DynamicsUpdateJob& self = static_cast<DynamicsUpdateJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_updaters[i]->update(*self.m_info);
    }
}

mm::mtl::IntrusivePtr<WindForceCalculator> WindForceCalculator::create() {
#line 31
    return new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) WindForceCalculator();
}

WindForceCalculator::~WindForceCalculator() {
    unbindProbe();
}

void WindForceCalculator::unbindProbe() {
    if (m_probe != nullptr) {
        m_probe->release();
        m_probe = nullptr;
    }
}

void WindForceCalculator::bindProbe(WindProbe& probe) {
    unbindProbe();
    m_probe = &probe;
    probe.addRef();
}

void WindForceCalculator::calcForce(float, const skd::DynamicsSolver& solver, mm::mtl::Vector<mm::Vec3>* pForces) {
    if (m_probe == nullptr) {
        return;
    }
    const wnd::WindProbe* probe = m_probe->m_pProbe;
    if (probe == nullptr || probe->m_pGlobalWind == nullptr) {
        return;
    }
    const mm::Vec3& globalWind = probe->m_blender.m_winds[(probe->m_windIndex + solver.m_index) % 12];
    mm::Quat rotation = probe->m_transform.rotation;
    mm::Quat inverse = mm::Quat::inverse(rotation);
    mm::Vec3 wind = inverse.rotate(globalWind);
    for (unsigned int i = 0; i < pForces->size(); i++) {
        const skd::ResNode& resNode = (*solver.m_nodes.m_pResNodes)[i];
        (*pForces)[i] = wind * resNode.m_windRate * m_scale;
    }
    if (probe->m_hitCaches.size() == 0) {
        return;
    }
    for (unsigned int i = 0; i < pForces->size(); i++) {
        const skd::ResNode& resNode = (*solver.m_nodes.m_pResNodes)[i];
        mm::Vec3 position;
        probe->m_transform.rotation.rotate(position, solver.m_nodes.m_nodes[i].m_pos);
        for (const wnd::LocalWindHitCache& hitCache : probe->m_hitCaches) {
            mm::Vec3 localWind;
            hitCache.pWind->calcEffectiveWind(position, &localWind);
            mm::Vec3 force = inverse.rotate(localWind);
            (*pForces)[i] += force * resNode.m_windRate * m_scale;
        }
    }
}

mm::mtl::RTTI WindForceCalculator::m_rtti("WindForceCalculator", &ForceCalculator::m_rtti, nullptr);

}  // namespace fw
