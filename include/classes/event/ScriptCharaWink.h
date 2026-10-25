#ifndef CLASSES_EVENT_SCRIPTCHARAWINK_H
#define CLASSES_EVENT_SCRIPTCHARAWINK_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F478
class ScriptCharaWink : public ::event::ITodo {
public:
    virtual ~ScriptCharaWink() {}  // slot 0
    virtual const char* cmdName() const { return "charawink"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5
};
}  // namespace event

#endif
