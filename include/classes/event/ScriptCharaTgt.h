#ifndef CLASSES_EVENT_SCRIPTCHARATGT_H
#define CLASSES_EVENT_SCRIPTCHARATGT_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F1F8
class ScriptCharaTgt : public ::event::ITodo {
public:
    virtual ~ScriptCharaTgt() {}  // slot 0
    virtual const char* cmdName() const { return "charatgt"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
