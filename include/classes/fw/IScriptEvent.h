#ifndef CLASSES_FW_ISCRIPTEVENT_H
#define CLASSES_FW_ISCRIPTEVENT_H

namespace fw { struct ScriptEventParam; }

namespace fw {
// what fw::ScriptManager tells about its scripts (1.0.0's table _ZTVN2fw12IScriptEventE, owned by ScriptManager.cpp:
// its destructors and scriptEvent; 3.0.1 has no listener left, so its linker dropped them; ScriptManager::addEvent
// and removeEvent queued and unqueued them in 1.0.0)
class IScriptEvent {
public:
    virtual ~IScriptEvent();  // slot 0
    virtual void scriptEvent(ScriptEventParam& param);  // slot 2
};
}  // namespace fw

#endif
