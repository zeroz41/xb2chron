#ifndef CLASSES_EVENT_IMANICALLBACK_H
#define CLASSES_EVENT_IMANICALLBACK_H

namespace event {
// table none (its derived classes')
class IManiCallback {
public:
    class RenderParam;
    class SetParam;
    class StartParam;
    virtual ~IManiCallback();  // slot 0
    virtual void OnManiStartPos(event::IManiCallback::StartParam&);  // slot 2
    virtual void OnManiSetPos(event::IManiCallback::SetParam&);  // slot 3
    virtual void OnManiStartRot(event::IManiCallback::StartParam&);  // slot 4
    virtual void OnManiSetRot(event::IManiCallback::SetParam&);  // slot 5
    virtual void OnManiStartTar(event::IManiCallback::StartParam&);  // slot 6
    virtual void OnManiSetTar(event::IManiCallback::SetParam&);  // slot 7
    virtual void OnManiRender(event::IManiCallback::RenderParam&);  // slot 8
};
}  // namespace event

#endif
