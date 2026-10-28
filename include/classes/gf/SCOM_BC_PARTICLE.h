#ifndef CLASSES_GF_SCOM_BC_PARTICLE_H
#define CLASSES_GF_SCOM_BC_PARTICLE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ABF8
class SCOM_BC_PARTICLE : public ::gf::SCOM {
public:
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // fields: fn_710056ABC4 / fn_710056ACD8 / fn_710056ADF4 fill them (the names are not the original's)
    GF_OBJ_HANDLE* m_obj;
    int m_step;                // 0: start the particle, 1: fade it out over m_time
    unsigned int m_particle;   // the object's attribute (DataParamAcc::getAttribute), or 0x11
    float m_time;              // the time left
    float m_totalTime;
    bool m_isStop;             // the time does not run while set
};
}  // namespace gf

#endif
