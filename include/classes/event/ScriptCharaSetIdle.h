#ifndef CLASSES_EVENT_SCRIPTCHARASETIDLE_H
#define CLASSES_EVENT_SCRIPTCHARASETIDLE_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F2B8
class ScriptCharaSetIdle : public ::event::ITodo {
public:
    virtual ~ScriptCharaSetIdle();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
};
}  // namespace event

#endif
