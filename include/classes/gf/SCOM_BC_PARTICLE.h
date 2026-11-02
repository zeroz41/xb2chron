#ifndef CLASSES_GF_SCOM_BC_PARTICLE_H
#define CLASSES_GF_SCOM_BC_PARTICLE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ABF8
class SCOM_BC_PARTICLE : public ::gf::SCOM {
public:
    // type 77 for obj's particle over time; defined (inline) in gf_req_scom.cpp, the one unit that builds it
    SCOM_BC_PARTICLE(GF_OBJ_HANDLE* obj, float time);
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // Placeholder names: nothing in 1.0.0's symbols names them. Members because each builds SCOM_BC_PARTICLE
    // (its table) next to its exec. Each queues the request unless obj is -1 or time is below 1e-6 (then -1);
    // fn_710056ACD8 sets particle 10, fn_710056ADF4 particle 10 with the stop flag (callers: BladeChangeManager's
    // procs, BattleCharacter; fn_71002CB9A8; GfGameScene::fn_71002C79B8)
    static unsigned long fn_710056ABC4(GF_OBJ_HANDLE* obj, float time);
    static unsigned long fn_710056ACD8(GF_OBJ_HANDLE* obj, float time);
    static unsigned long fn_710056ADF4(GF_OBJ_HANDLE* obj, float time);

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
