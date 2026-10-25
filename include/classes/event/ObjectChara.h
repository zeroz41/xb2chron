#ifndef CLASSES_EVENT_OBJECTCHARA_H
#define CLASSES_EVENT_OBJECTCHARA_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "classes/event/Object.h"

namespace mm { class Col4; }
namespace event { class PosAxis; class RotAxis; }

namespace event {
// table 0x7100B3DD70 (its first slots are event::Object's)
class ObjectChara : public ::event::Object {
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
    virtual bool isLoading() const;  // slot 10
    virtual void OnManiStartPos(event::IManiCallback::StartParam&);  // slot 11
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 12
    virtual void OnManiStartRot(event::IManiCallback::StartParam&);  // slot 13
    virtual void OnManiSetRot(event::IManiCallback::SetParam&);  // slot 14
    virtual void OnManiStartTar(event::IManiCallback::StartParam&);  // slot 15
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 16
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 17
    void setPosAxis(const PosAxis& pos);
    void setRotAxis(const RotAxis& rot);
};
}  // namespace event

#endif
