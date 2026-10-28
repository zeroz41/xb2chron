#ifndef CLASSES_GF_SCOM_DEAD_PARTICLE_H
#define CLASSES_GF_SCOM_DEAD_PARTICLE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ABC8
class SCOM_DEAD_PARTICLE : public ::gf::SCOM {
public:
    SCOM_DEAD_PARTICLE(SCOM_TYPE type, unsigned long handle, GF_OBJ_HANDLE* obj, unsigned int particle, float time)
        : SCOM(type, handle), m_obj(obj), m_step(0), m_particle(particle), m_time(time), m_totalTime(time) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(GF_OBJ_HANDLE* obj, unsigned int particle, float time);

    // (the field names are not the original's)
    GF_OBJ_HANDLE* m_obj;
    int m_step;                // 0: start the particle once the animation ends, 1: fade it out over m_time
    unsigned int m_particle;
    float m_time;              // the time left
    float m_totalTime;
};
}  // namespace gf

#endif
