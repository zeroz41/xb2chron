#ifndef CLASSES_EVENT_SCRIPTCHARAACTION_H
#define CLASSES_EVENT_SCRIPTCHARAACTION_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F2F8
class ScriptCharaAction : public ::event::ITodo {
public:
    virtual ~ScriptCharaAction() {}  // slot 0
    virtual const char* cmdName() const { return "charaact"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
