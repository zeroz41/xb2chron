#ifndef CLASSES_EVENT_CAMFREE_H
#define CLASSES_EVENT_CAMFREE_H

#include "classes/event/CamBase.h"
#include "classes/ml/IWorkEvent.h"
#include "mm/Pnt.h"

namespace event { class FrameInfo; }
namespace ml { class EventView; }
namespace mm { class Mat44; }

namespace event {
// table 0x7100B3C818
class CamFree : public ::event::CamBase, public ::ml::IWorkEvent {
public:
    // inline: CamManager's constructor (1.0.0 0x71000B5DE8, inlined in Singleton<CamManager>::getPtr) builds it
    CamFree() : m_flags(0), pad_49(0), pad_4a(0), pad_4c(0), pad_50(0), pad_54(5.0f), pad_60(0) {
    }
    virtual ~CamFree();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    // the mouse and key slots return whether they took the event (w0 is set on every path)
    virtual bool OnMouseButtonDown(ml::EventView*);  // slot 5
    virtual bool OnMouseMove(ml::EventView*);  // slot 6
    virtual bool OnMouseButtonUp(ml::EventView*);  // slot 7
    virtual bool OnKeyUp(ml::EventView*);  // slot 8 (returns whether it took the key)
    virtual bool OnKeyDown(ml::EventView*);  // slot 9
    void ctrlTumble(mm::Pnt<int> const&);
    void ctrlDolly(mm::Pnt<int> const&);
    void getScreenMove2TargetMove(mm::Vec3&, mm::Pnt<int> const&) const;
    void getViewMatrix(mm::Mat44&) const;
    // inline: moves the eye (pad_10) and the target (pad_20) by the screen move pnt, faster with pad_54 (OnMouseMove's
    // mode 2 and OnKeyDown's 0x82/0x84/0x86/0x88 keys inline the same code); the name is not the original's
    void moveScreen(const mm::Pnt<int>& pnt) {
        float speed = pad_54 * 0.2f;
        if (speed > 1.0f) {
            speed *= 20.0f;
        }
        mm::Vec3 move;
        getScreenMove2TargetMove(move, pnt);
        mm::Vec3 d = move * speed;
        pad_10 = pad_10 + d;
        pad_20 = pad_20 + d;
    }
    // bit 0 is set while the camera is attached to the scene's view: the destructor then detaches it (ml::WinView's
    // detachWorkEvent); the name is not the original's
    unsigned char m_flags;  // 0x48
    unsigned char pad_49;
    unsigned short pad_4a;
    unsigned int pad_4c;
    // 0x50: the drag mode the mouse buttons pick while bit 3 of pad_4c (a key) is held: 1 ctrlDolly, 2 a target
    // move, 3 ctrlTumble (OnMouseMove); 0 from the constructor
    int pad_50;
    float pad_54;  // 0x54: 5 from the constructor
    unsigned char pad_58[0x8];
    unsigned int pad_60;  // 0x60
};
}  // namespace event

#endif
