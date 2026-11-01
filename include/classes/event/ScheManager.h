#ifndef CLASSES_EVENT_SCHEMANAGER_H
#define CLASSES_EVENT_SCHEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/Scheduler.h"

namespace event { enum MSG_TYPE : int; class Scheduler; }

namespace event {
// table 0x7100B3D580; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ScheManager>
class ScheManager : public IManager, public mm::mtl::Singleton<ScheManager> {
public:
    virtual ~ScheManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // the inlined getPtr's constructor zeroes only the word at 0x10
    ScheManager() : pad_10(0) {}
    // clears the step flag of handle's scheduler (the first scheduler with that handle); the name is not the original's
    void cancelStep(gf::GF_OBJ_HANDLE* handle, unsigned int flag) {
        for (Scheduler** it = m_schedulers.begin(); it != m_schedulers.end(); ++it) {
            if ((*it)->m_handle == handle) {
                if ((*it)->m_flags & flag) {
                    (*it)->m_flags &= ~flag;
                }
                return;
            }
        }
    }
    // clears the look step (flag 0x10) of handle's scheduler (inlined by ScriptCharaTgt::doit, which aims the
    // character itself); the name is not the original's
    void cancelLook(gf::GF_OBJ_HANDLE* handle) { cancelStep(handle, 0x10); }
    // clears the turn step (flag 0x4) of handle's scheduler (inlined by ScriptCharaTurnRot::doit, which turns the
    // character itself); the name is not the original's
    void cancelTurn(gf::GF_OBJ_HANDLE* handle) { cancelStep(handle, 0x4); }
    // whether a scheduler still runs its motion-end/turn chain: any scheduler for handle -1, else handle's
    // (inlined by CharaPlayTalkAuto/CharaPlayActionAuto::update, which wait for it); the name is not the original's
    bool isTurnBusy(gf::GF_OBJ_HANDLE* handle) {
        if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            for (Scheduler** it = m_schedulers.begin(); it != m_schedulers.end(); ++it) {
                if ((*it)->m_turnFunc) {
                    return true;
                }
            }
        } else {
            for (Scheduler** it = m_schedulers.begin(); it != m_schedulers.end(); ++it) {
                if ((*it)->m_handle == handle && (*it)->m_turnFunc) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    unsigned int pad_10;
    unsigned int pad_14;
    // the schedulers push creates; update runs Scheduler::exec on each; the name is not the original's
    mm::mtl::FixedVector<Scheduler*, 16> m_schedulers;  // 0x18 (count at 0x98)
};
}  // namespace event

#endif
