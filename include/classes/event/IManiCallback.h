#ifndef CLASSES_EVENT_IMANICALLBACK_H
#define CLASSES_EVENT_IMANICALLBACK_H

#include "mm/Mat44.h"
#include "mm/Col4.h"

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

// what the manipulator passes the OnManiSet* slots: a matrix at 0x80 whose last row is the position
// (ObjectChara/ObjectEffect::OnManiSetPos take that row; ObjectChara::OnManiSetRot reads the axis rows); the
// field name is not the original's
class IManiCallback::SetParam {
public:
    unsigned char pad_0[0x80];
    mm::Mat44 m_mtx;  // 0x80
};
// what ManiManager::render passes OnManiRender: the colour to draw the target in; the field name is not the
// original's
class IManiCallback::RenderParam {
public:
    mm::Col4 m_color;  // 0x0
};
}  // namespace event

#endif
