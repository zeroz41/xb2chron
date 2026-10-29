#ifndef CLASSES_EVENT_OBJECTCAMERA_H
#define CLASSES_EVENT_OBJECTCAMERA_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/Object.h"
#include "classes/event/CamObj.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3DE68
class ObjectCamera : public ::event::Object {
public:
    virtual ~ObjectCamera();  // slot 0
    virtual bool OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual bool OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual bool OnManiStartTar(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 14
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 15
    // the camera the object drives (tail calls its slot 4, CamObj::tail); the name is not the original's
    CamObj* m_cam;  // 0x68
};
}  // namespace event

#endif
