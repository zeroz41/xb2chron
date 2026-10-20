#ifndef CLASSES_EVENT_OBJECTCAMERA_H
#define CLASSES_EVENT_OBJECTCAMERA_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/Object.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3DE68
class ObjectCamera : public ::event::Object {
public:
    virtual ~ObjectCamera();  // slot 0
    virtual void OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual void OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual void OnManiStartTar(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 14
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 15
};
}  // namespace event

#endif
