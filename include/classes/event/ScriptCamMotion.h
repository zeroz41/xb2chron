#ifndef CLASSES_EVENT_SCRIPTCAMMOTION_H
#define CLASSES_EVENT_SCRIPTCAMMOTION_H

namespace event { class Param; }

namespace event {
// table 0x7100B3F538
class ScriptCamMotion {
public:
    virtual ~ScriptCamMotion();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
