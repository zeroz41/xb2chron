#ifndef CLASSES_EVENT_CHARADYSUPDATER_H
#define CLASSES_EVENT_CHARADYSUPDATER_H
#include "classes/gf/GfComDynamics.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjUtil.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3CAD8
class CharaDysUpdater {
public:
    virtual ~CharaDysUpdater() {}  // slot 0
    // 1.0.0's CharaDysUpdater::resetMovement(int) (0x71000BD580): resets the object's dynamics movement, sets
    // bit 1 of m_flags and keeps the value; inline in 3.0.1 (the liner commands' updates)
    void resetMovement(int value) {
        if (gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle)) {
            if (gf::GfComDynamics* dynamics = obj->getComponent<gf::GfComDynamics>(8)) {
                dynamics->resetMovement();
            }
        }
        m_flags |= 2;
        m_movement = value;
    }
    // 1.0.0's CharaDysUpdater::resetDynamics(int): asks the dynamics updater for a reset and resets its
    // movement, sets bit 0 of m_flags and keeps the value; inline in 3.0.1 (CharaObj::resetDynamics)
    void resetDynamics(int value) {
        if (gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle)) {
            if (gf::GfComDynamics* dynamics = obj->getComponent<gf::GfComDynamics>(8)) {
                dynamics->m_updater.m_resetRequest = true;
                dynamics->resetMovement();
            }
        }
        m_flags |= 1;
        m_dynamics = value;
    }
    // bit 0: resetDynamics, bit 1: resetMovement (1.0.0's); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned int pad_c;
    // the character's gf object (CharaObj::initModel stores it); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    int m_dynamics;  // 0x18 1.0.0's resetDynamics(int) stores its value (the name is not the original's)
    int m_movement;  // 0x1c 1.0.0's resetMovement(int) stores its value (the name is not the original's)
};
}  // namespace event

#endif
