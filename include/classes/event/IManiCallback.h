#ifndef CLASSES_EVENT_IMANICALLBACK_H
#define CLASSES_EVENT_IMANICALLBACK_H

namespace event {
// table none (its derived classes')
class IManiCallback {
public:
    class RenderParam;
    class SetParam;
    class StartParam;
    virtual ~IManiCallback() {}  // slot 0: inline (no copy in the module; event::Object's destructor stores no base table)
    // the Start slots return false here (inline: CharaObj.cpp keeps the copies event::ObjectLight's table holds; the
    // bool return is proven by the code, `mov w0, wzr`)
    virtual bool OnManiStartPos(event::IManiCallback::StartParam&) { return false; }  // slot 2
    virtual void OnManiSetPos(event::IManiCallback::SetParam&) {}  // slot 3
    virtual bool OnManiStartRot(event::IManiCallback::StartParam&) { return false; }  // slot 4
    virtual void OnManiSetRot(event::IManiCallback::SetParam&) {}  // slot 5
    virtual bool OnManiStartTar(event::IManiCallback::StartParam&) { return false; }  // slot 6
    virtual void OnManiSetTar(event::IManiCallback::SetParam&) {}  // slot 7
    virtual void OnManiRender(event::IManiCallback::RenderParam&) {}  // slot 8
};
}  // namespace event

#endif
