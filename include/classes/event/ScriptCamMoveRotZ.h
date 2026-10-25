#ifndef CLASSES_EVENT_SCRIPTCAMMOVEROTZ_H
#define CLASSES_EVENT_SCRIPTCAMMOVEROTZ_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F738
class ScriptCamMoveRotZ : public ::event::ITodo {
public:
    virtual ~ScriptCamMoveRotZ() {}  // slot 0
    virtual const char* cmdName() const { return "camrotz"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
