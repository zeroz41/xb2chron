#ifndef CLASSES_EVENT_SCRIPTPLAYTEXT_H
#define CLASSES_EVENT_SCRIPTPLAYTEXT_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3FAB8
class ScriptPlayText : public ::event::ITodo {
public:
    virtual ~ScriptPlayText() {}  // slot 0
    virtual const char* cmdName() const { return "text"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
};
}  // namespace event

#endif
