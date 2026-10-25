#ifndef CLASSES_EVENT_SCRIPTCHARATURNROT_H
#define CLASSES_EVENT_SCRIPTCHARATURNROT_H

#include "classes/event/ITodo.h"
#include "classes/event/RotAxis.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F1B8
class ScriptCharaTurnRot : public ::event::ITodo {
public:
    virtual ~ScriptCharaTurnRot() {}  // slot 0
    virtual const char* cmdName() const { return "charaturnrot"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5

    // the active object's rotation before doit, which undo restores; the name is not the original's
    RotAxis m_prevRot;  // 0x10
};
}  // namespace event

#endif
