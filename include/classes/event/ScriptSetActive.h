#ifndef CLASSES_EVENT_SCRIPTSETACTIVE_H
#define CLASSES_EVENT_SCRIPTSETACTIVE_H

#include "classes/event/ITodo.h"

namespace event { class Object; }
namespace event { class Param; }

namespace event {
// table 0x7100B3F138
class ScriptSetActive : public ::event::ITodo {
public:
    virtual ~ScriptSetActive() {}  // slot 0
    virtual const char* cmdName() const { return "setactive"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5

    // the current scene's active object before doit, which undo restores; the name is not the original's
    Object* m_prevActive;  // 0x8
};
}  // namespace event

#endif
