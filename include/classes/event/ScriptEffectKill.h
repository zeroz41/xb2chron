#ifndef CLASSES_EVENT_SCRIPTEFFECTKILL_H
#define CLASSES_EVENT_SCRIPTEFFECTKILL_H

namespace event { class Param; }

namespace event {
// table 0x7100B3F938
class ScriptEffectKill {
public:
    virtual ~ScriptEffectKill();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&) {}  // slot 4
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
