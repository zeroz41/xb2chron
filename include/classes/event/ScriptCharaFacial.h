#ifndef CLASSES_EVENT_SCRIPTCHARAFACIAL_H
#define CLASSES_EVENT_SCRIPTCHARAFACIAL_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F3F8
class ScriptCharaFacial : public ::event::ITodo {
public:
    virtual ~ScriptCharaFacial() {}  // slot 0
    virtual const char* cmdName() const { return "charafacial"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
