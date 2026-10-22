#include "anm/JobQueue.h"
#include "classes/fw/SensorManager.h"

namespace fw {

const char* SensorUpdateJob::_TYPE_NAME = "SensorUpdateJob";

SensorUpdateJob::SensorUpdateJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(SensorUpdateJob), 0), m_count(count) {
    m_updaters[0] = nullptr;
    m_updaters[1] = nullptr;
}

void SensorUpdateJob::exec(anm::Job& job) {
    SensorUpdateJob& self = static_cast<SensorUpdateJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_updaters[i]->m_delegate();
    }
}

}  // namespace fw
