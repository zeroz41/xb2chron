#ifndef CLASSES_EVENT_IBOUCALLBACK_H
#define CLASSES_EVENT_IBOUCALLBACK_H

namespace event {
// table none (its derived classes')
class IBouCallback {
public:
    class RenderParam;
    class SelectParam;
    virtual ~IBouCallback();  // slot 0
    virtual void OnBouRectSelect(event::IBouCallback::SelectParam const&);  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&);  // slot 3
};
}  // namespace event

#endif
