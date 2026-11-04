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
    // 2.0.0's symbols name them. Each queues the request unless obj is -1 or time is below 1e-6 (then -1); createPortal
    // sets particle 10, createPortalEvt particle 10 with the stop flag (callers: BladeChangeManager's procs,
    // BattleCharacter; updatePortalFade; GfGameScene::gevOpenPortal)
    static unsigned long create(GF_OBJ_HANDLE* obj, float time);
    static unsigned long createPortal(GF_OBJ_HANDLE* obj, float time);
    static unsigned long createPortalEvt(GF_OBJ_HANDLE* obj, float time);

    // fields: create / createPortal / createPortalEvt fill them (the names are not the original's)
    GF_OBJ_HANDLE* m_obj;
    int m_step;                // 0: start the particle, 1: fade it out over m_time
    unsigned int m_particle;   // the object's attribute (DataParamAcc::getAttribute), or 0x11
    float m_time;              // the time left
    float m_totalTime;
    bool m_isStop;             // the time does not run while set
};
}  // namespace gf

#endif
