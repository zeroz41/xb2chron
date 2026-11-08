#ifndef CLASSES_EVENT_SHAKEMANAGER_H
#define CLASSES_EVENT_SHAKEMANAGER_H

#include "classes/event/Shaker.h"
#include "mm/mtl/FixStr.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D4F8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ShakeManager>
class ShakeManager : public IManager, public mm::mtl::Singleton<ShakeManager> {
public:
    // inline: D2/D0 and the thunks sit in CharaObj's tail; OnEventProc is the key function. Written
    // `inline`: the hint's threshold lets D0 and the thunks inline the whole D2 as the original's do (cost 275 > 275)
    virtual inline ~ShakeManager() {}  // slot 0
    // out of line at 0x71001008A0 and inlined into Singleton<ShakeManager>::get (0x710013B4D4)
    ShakeManager();
    void play(const char* name, float p0, float p1, float p2);
    void setIdleShake(bool enable);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    static const mm::mtl::FixStr<32> s_names[4];  // the shake types' names
    // 1.0.0 has it out of line (0x71000EDE80); 3.0.1 inlines it into OnEventProc
    void clear();
    void update();
    // Manager's destructor runs it on Singleton<ShakeManager>::get(): clear, the shaker destroyed and the three
    // words after it zeroed (the name is not the original's)
    void term() {
        clear();
        m_shaker.destroy();
        m_idleResId = 0;
        m_resIds[3] = 0;
        m_resIds[2] = 0;
        m_resIds[1] = 0;
        m_resIds[0] = 0;
    }
    // 1.0.0 has it out of line (0x71000EDFC0); 3.0.1 inlines it into update and setIdleShake: the idle shake
    // resumed when enabled, the shaker stopped otherwise
    void idle() {
        if (m_flags & 1) {
            m_shaker.play(m_idleResId, -1.0f, -1.0f, -1.0f);
        } else {
            m_shaker.stop();
        }
        m_flags &= ~2u;
    }

    // bit 0: idle shake enabled (setIdleShake), bit 1: play's shake running (update resumes the idle one after
    // it); the name is not the original's
    unsigned int m_flags;  // @0x10
    unsigned char pad_0x14[0x4];
    Shaker m_shaker;  // @0x18 (the constructor stores event::Shaker's table there); the name is not the original's
    // the shaker resource of each s_names type (create stores them, play picks one); zeroed by term (Manager's
    // destructor); the name is not the original's
    unsigned int m_resIds[4];  // 0xca8
    unsigned int m_idleResId;  // 0xcb8: setIdleShake's resource; the name is not the original's
    // the instance is 0xCC0 bytes
};
}  // namespace event

#endif
