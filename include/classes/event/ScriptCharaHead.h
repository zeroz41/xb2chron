#ifndef CLASSES_EVENT_SCRIPTCHARAHEAD_H
#define CLASSES_EVENT_SCRIPTCHARAHEAD_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F3B8
class ScriptCharaHead : public ::event::ITodo {
public:
    virtual ~ScriptCharaHead() {}  // slot 0
    virtual const char* cmdName() const { return "charahead"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
