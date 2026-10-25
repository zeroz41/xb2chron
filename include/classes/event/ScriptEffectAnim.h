#ifndef CLASSES_EVENT_SCRIPTEFFECTANIM_H
#define CLASSES_EVENT_SCRIPTEFFECTANIM_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3FA78
class ScriptEffectAnim : public ::event::ITodo {
public:
    virtual ~ScriptEffectAnim() {}  // slot 0
    virtual const char* cmdName() const { return "effanim"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
};
}  // namespace event

#endif
