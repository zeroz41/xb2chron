#ifndef CLASSES_EVENT_SCRIPTCAMFOLLOWPOS_H
#define CLASSES_EVENT_SCRIPTCAMFOLLOWPOS_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F7F8
class ScriptCamFollowPos : public ::event::ITodo {
public:
    virtual ~ScriptCamFollowPos() {}  // slot 0
    virtual const char* cmdName() const { return "camflwpos"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5

    // the camera's follow flag before doit, which undo restores; the name is not the original's
    bool m_prevFollow;  // 0x8
};
}  // namespace event

#endif
