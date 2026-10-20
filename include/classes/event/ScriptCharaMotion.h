#ifndef CLASSES_EVENT_SCRIPTCHARAMOTION_H
#define CLASSES_EVENT_SCRIPTCHARAMOTION_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F338
class ScriptCharaMotion : public ::event::ITodo {
public:
    virtual ~ScriptCharaMotion();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
};
}  // namespace event

#endif
