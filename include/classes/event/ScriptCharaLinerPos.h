#ifndef CLASSES_EVENT_SCRIPTCHARALINERPOS_H
#define CLASSES_EVENT_SCRIPTCHARALINERPOS_H

#include "classes/event/ITodo.h"
#include "classes/event/PosAxis.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F238
class ScriptCharaLinerPos : public ::event::ITodo {
public:
    virtual ~ScriptCharaLinerPos() {}  // slot 0
    virtual const char* cmdName() const { return "charalinerpos"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5

    // the active object's position before doit, which undo restores; the name is not the original's
    PosAxis m_prevPos;  // 0x10
};
}  // namespace event

#endif
