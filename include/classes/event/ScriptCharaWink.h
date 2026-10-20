#ifndef CLASSES_EVENT_SCRIPTCHARAWINK_H
#define CLASSES_EVENT_SCRIPTCHARAWINK_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F478
class ScriptCharaWink : public ::event::ITodo {
public:
    virtual ~ScriptCharaWink();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
