#ifndef CLASSES_EVENT_SCRIPTCHARAFADE_H
#define CLASSES_EVENT_SCRIPTCHARAFADE_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F4F8
class ScriptCharaFade : public ::event::ITodo {
public:
    virtual ~ScriptCharaFade() {}  // slot 0
    virtual const char* cmdName() const { return "charafade"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5

    // the character's fade flag before doit, which undo restores; the name is not the original's
    bool m_prevFade;  // 0x8
};
}  // namespace event

#endif
