#ifndef CLASSES_EVENT_OBJECTCHARA_H
#define CLASSES_EVENT_OBJECTCHARA_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"

namespace mm { class Col4; }

namespace event {
// a base of event::ObjectChara no evidence names yet
class TUnk_B3DD70 {
public:
    virtual ~TUnk_B3DD70();
    virtual void OnBouRectSelect(event::IBouCallback::SelectParam const&) = 0;
    virtual void OnBouRender(event::IBouCallback::RenderParam const&) = 0;
    virtual void clear() = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void update() = 0;
    virtual void render(mm::Col4 const&) = 0;
    virtual void tail() = 0;
    virtual void isLoading() const = 0;
    virtual void OnManiStartPos(event::IManiCallback::StartParam&) = 0;
    virtual void OnManiSetPos(event::IManiCallback::SetParam&) = 0;
    virtual void OnManiStartRot(event::IManiCallback::StartParam&) = 0;
    virtual void OnManiSetRot(event::IManiCallback::SetParam&) = 0;
    virtual void OnManiStartTar(event::IManiCallback::StartParam&) = 0;
    virtual void OnManiSetTar(event::IManiCallback::SetParam&) = 0;
    virtual void OnManiRender(event::IManiCallback::RenderParam&) = 0;
};
// a base of event::ObjectChara no evidence names yet
class TUnk_B3DE10 {
public:
    virtual ~TUnk_B3DE10();
    virtual void OnManiStartPos(event::IManiCallback::StartParam&) = 0;
    virtual void OnManiSetPos(event::IManiCallback::SetParam&) = 0;
    virtual void OnManiStartRot(event::IManiCallback::StartParam&) = 0;
    virtual void OnManiSetRot(event::IManiCallback::SetParam&) = 0;
    virtual void OnManiStartTar(event::IManiCallback::StartParam&) = 0;
    virtual void OnManiSetTar(event::IManiCallback::SetParam&) = 0;
    virtual void OnManiRender(event::IManiCallback::RenderParam&) = 0;
};
// table 0x7100B3DD70; base at 0x0 unknown (TUnk_B3DD70), base at 0x8 unknown (TUnk_B3DE10)
class ObjectChara : public TUnk_B3DD70, public TUnk_B3DE10 {
public:
    virtual ~ObjectChara();  // slot 0
    virtual void OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
    virtual void clear();  // slot 4
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual void isLoading() const;  // slot 10
    virtual void OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual void OnManiStartRot(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetRot(event::IManiCallback::SetParam&);  // slot 14
    virtual void OnManiStartTar(event::IManiCallback::StartParam&);  // slot 15
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 16
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 17
};
}  // namespace event

#endif
