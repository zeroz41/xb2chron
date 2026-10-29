#ifndef CLASSES_EVENT_EFFECTOBJ_H
#define CLASSES_EVENT_EFFECTOBJ_H

#include "classes/event/CmdQueue.h"
#include "classes/event/EffectCtrl.h"
#include "mm/Vec3.h"

namespace event {
// table 0x7100B3CE90
class EffectObj {
public:
    virtual ~EffectObj();  // slot 0
    void playAnim(const char* name, float frame);
    void play(const char* name, float a, float b, float c, int d, int e);
    void stop();

    unsigned char pad_8[0x48];
    EffectCtrl m_ctrl;  // 0x50; the name is not the original's
    unsigned char pad_58[0x178];
    // the scale ScriptEffectScale sets on all three axes (doit saves it first, undo restores it); the name is not
    // the original's
    mm::Vec3 m_scale;  // 0x1d0
    // 1.0.0's EffectObj::end (0x71000DCE8C; 3.0.1 inlines it into ObjectEffect::end): the queued commands erased
    // first to last, then the effect killed
    void end() {
        m_cmdQueue.eraseAll();
        m_ctrl.kill();
    }
    unsigned char pad_1e0[0x80];
    CmdQueue<6, 0> m_cmdQueue;  // 0x260; erased by end (CmdQueue<6,0>::erase); the name is not the original's
};
}  // namespace event

#endif
