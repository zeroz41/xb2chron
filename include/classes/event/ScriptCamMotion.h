#ifndef CLASSES_EVENT_SCRIPTCAMMOTION_H
#define CLASSES_EVENT_SCRIPTCAMMOTION_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F538
class ScriptCamMotion : public ::event::ITodo {
public:
    virtual ~ScriptCamMotion() {}  // slot 0
    virtual const char* cmdName() const { return "cammotion"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5
};
}  // namespace event

#endif
