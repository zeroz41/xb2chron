#ifndef CLASSES_EVENT_CAMBASE_H
#define CLASSES_EVENT_CAMBASE_H

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table none (its derived classes')
class CamBase {
public:
    virtual ~CamBase() {}  // slot 0
    virtual void update(event::FrameInfo const&) = 0;  // slot 2
    virtual void render(mm::Col4 const&) {}  // slot 3
    virtual void tail() {}  // slot 4
    unsigned char pad_8[0x30];  // fields: size from its derived classes
    // the near and far clip distances ScriptCamNearfar sets from EVT_nearfar; the name is not the original's
    float m_near;  // 0x38
    float m_far;   // 0x3c
};
}  // namespace event

#endif
