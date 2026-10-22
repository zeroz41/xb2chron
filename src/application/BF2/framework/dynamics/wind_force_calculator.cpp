#include "classes/fw/DyanmicsManager.h"
#include "classes/fw/WindForceCalculator.h"
#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/WindProbe.h"
#include "classes/mm/mtl/IAllocator.h"

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

mm::mtl::RTTI WindForceCalculator::m_rtti("WindForceCalculator", &ForceCalculator::m_rtti, nullptr);

}  // namespace fw
