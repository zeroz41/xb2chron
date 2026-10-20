#ifndef CLASSES_EVENT_CAMOBJ_H
#define CLASSES_EVENT_CAMOBJ_H

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3C970
class CamObj {
public:
    class SetEnable;
    class SetFov;
    class SetNearfar;
    class SetTargetPos;
    virtual ~CamObj();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void render(mm::Col4 const&);  // slot 3
    virtual void tail();  // slot 4
};
}  // namespace event

#endif
