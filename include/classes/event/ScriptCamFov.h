#ifndef CLASSES_EVENT_SCRIPTCAMFOV_H
#define CLASSES_EVENT_SCRIPTCAMFOV_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F678
class ScriptCamFov : public ::event::ITodo {
public:
    virtual ~ScriptCamFov() {}  // slot 0
    virtual const char* cmdName() const { return "camfov"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5

    // the camera's field of view before doit, which undo restores; the name is not the original's
    float m_prevFov;  // 0x8
};
}  // namespace event

#endif
