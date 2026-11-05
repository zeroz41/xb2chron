#ifndef CLASSES_EVENT_DOFMANAGER_H
#define CLASSES_EVENT_DOFMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; class CharaObj; }

namespace event {
// table 0x7100B3CDC0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::DofManager>
class DofManager : public IManager, public mm::mtl::Singleton<DofManager> {
public:
    // out of line: Singleton<DofManager>::getPtr hands __cxa_atexit its D1 (an alias of a strong D2), which an inline empty
    // destructor would let the optimizer drop (evt_post's entries keep the call)
    virtual ~DofManager();  // slot 0
    // out of line (0x71000EF0AC; Singleton<DofManager>::getPtr calls it): 0x18 = 1, 0x24/0x34 = 5, 0x30 = 0.1,
    // 0x38 = 0.6, 0x3c = 4, 0x40 = 1, 0x50 = "", the rest 0
    DofManager();
    // evt_post.playDof's entries (the plain and the detailed form)
    void play(int type, int frame);
    void play(int type, float p0, float p1, float p2, float p3, float p4, float p5, int frame, bool flag,
              const char* name);
    void playSimple(int type, int frame);
    // update's focus distance for play's type (static: the type comes in w0, the distance in s0)
    static float calcDist(int type, float dist);
    // render's label for an axis (static: the axis comes in w0)
    static const char* getAxisName(int axis);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's clear() (0x71000D88D4) only calls stop()
    void clear();
    void stop();
    void update();
    void render();
    // static (the character comes in x0; calcDist is its caller): the camera eye's distance to the point above
    // the character, scaled by the cosine between that direction and the first camera interface's m_target taken
    // as a direction; the float is not read
    static float calcDistSub(CharaObj* chara, float);

    // fields play() sets; what they hold is not known yet (play(int, int) reads them from EVT_dof's "dist", "range",
    // "pixel", "lens", "strength", "blend" columns, in that order)
    unsigned int pad_10;
    unsigned int pad_14;  // bits 0 and 1 set by play
    int pad_18;  // play's type
    float pad_1c;  // play's first float (twice: 0x1c and 0x20)
    float pad_20;
    float pad_24;
    bool pad_28;  // cleared by play
    unsigned char pad_29[0x3];
    int pad_2c;  // the constructor's 0; playSimple's first argument (update and stop hand it to setDOFFocusNum)
    float pad_30;  // the constructor's 0.1; playSimple's "foMin" (update and stop hand it to setDOFFocusMin)
    float pad_34;
    float pad_38;
    float pad_3c;
    float pad_40;
    int pad_44;  // play's frame count
    bool pad_48;
    unsigned char pad_49[0x7];
    const char* pad_50;  // play's name
};
}  // namespace event

#endif
