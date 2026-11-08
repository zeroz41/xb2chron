#ifndef CLASSES_EVENT_IBOUCALLBACK_H
#define CLASSES_EVENT_IBOUCALLBACK_H

#include "mm/Col4.h"

namespace event {
class BouRect;
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
// what BouManager::updateActive passes OnBouRectSelect: its drag rectangle (ObjectChara/ObjectEffect::
// OnBouRectSelect test their position with it); the field name is not the original's
class IBouCallback::SelectParam {
public:
    const BouRect* m_rect;  // 0x0
};
// what BouManager::render passes OnBouRender: the colour to draw the selected objects in; the field name is not
// the original's
class IBouCallback::RenderParam {
public:
    mm::Col4 m_color;  // 0x0
};
}  // namespace event

#endif
