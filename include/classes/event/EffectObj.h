#ifndef CLASSES_EVENT_EFFECTOBJ_H
#define CLASSES_EVENT_EFFECTOBJ_H

#include "classes/event/CmdQueue.h"
#include "classes/event/EffectCtrl.h"
#include "mm/Vec3.h"
#include "mm/Col4.h"
#include "event/CvType.h"
#include "classes/event/EffectLinearPos.h"
#include "classes/event/EffectLinearRot.h"
#include "classes/event/EffectLinearCol.h"

namespace event {
// table 0x7100B3CE90
class EffectObj {
public:
    virtual ~EffectObj();  // slot 0
    void playAnim(const char* name, float frame);
    void play(const char* name, float a, float b, float c, int d, int e);
    void stop();
    // named by the symbols: queue a move / turn of the effect to the vector over the time
    void moveTo(const mm::Vec3& pos, float time, CV_TYPE type);
    void turnTo(const mm::Vec3& rot, float time, CV_TYPE type);
    // fades m_color to the colour over the time (ScriptEffectColor::doit)
    void colorTo(const mm::Col4& color, float time, CV_TYPE type);

    unsigned char pad_8[0x48];
    EffectCtrl m_ctrl;  // 0x50; the name is not the original's
    // 1.0.0's EffectObj::end (0x71000DCE8C; 3.0.1 inlines it into ObjectEffect::end): the queued commands erased
    // first to last, then the effect killed
    void end() {
        m_cmdQueue.eraseAll();
        m_ctrl.kill();
    }
    unsigned char pad_1f0[0x70];
    CmdQueue<6, 0> m_cmdQueue;  // 0x260; erased by end (CmdQueue<6,0>::erase); the name is not the original's
    unsigned char pad_960[0x70];  // the EffectPlayEff (0x960) and EffectPlayEva (0x988) commands
    // the commands moveTo/turnTo/colorTo queue (the constructor builds them); the names are not the original's
    EffectLinearPos m_linearPos;  // 0x9d0
    EffectLinearRot m_linearRot;  // 0xbd0
    EffectLinearCol m_linearCol;  // 0xdd0
    unsigned long pad_fb8;
    unsigned int pad_fc0;
    // the step the linear commands advance their curves by each update; the name is not the original's
    float m_step;  // 0xfc4
    unsigned int pad_fc8;
};
}  // namespace event

#endif
