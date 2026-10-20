#ifndef CLASSES_EVENT_SCRIPTCAMROTZ_H
#define CLASSES_EVENT_SCRIPTCAMROTZ_H

namespace event { class Param; }

namespace event {
// table 0x7100B3F6F8
class ScriptCamRotZ {
public:
    virtual ~ScriptCamRotZ();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
