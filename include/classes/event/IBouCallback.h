#ifndef CLASSES_EVENT_IBOUCALLBACK_H
#define CLASSES_EVENT_IBOUCALLBACK_H

namespace event {
// table none (its derived classes')
class IBouCallback {
public:
    class RenderParam;
    class SelectParam;
    virtual ~IBouCallback() {}  // slot 0: inline (no copy in the module; event::Object's destructor stores no base table)
    // returns false here (inline: CharaObj.cpp keeps the copy event::ObjectLight's table holds); the bool return is
    // proven by the code (`mov w0, wzr`), the overriders return one too
    virtual bool OnBouRectSelect(event::IBouCallback::SelectParam const&) { return false; }  // slot 2
    virtual void OnBouRender(event::IBouCallback::RenderParam const&) {}  // slot 3
};
}  // namespace event

#endif
