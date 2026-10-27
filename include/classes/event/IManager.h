#ifndef CLASSES_EVENT_IMANAGER_H
#define CLASSES_EVENT_IMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// the event managers' base: 1.0.0 names its OnEventProc (event::IManager::OnEventProc, a `ret` that
// AreaeffManager's and BlockManager's tables hold at slot 2); event::Manager keeps the managers in a list and sends
// each message to all of them through slot 2. It has no table of its own (each manager's table holds its slots).
class IManager {
public:
    virtual ~IManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE) {}  // slot 2
};
}  // namespace event

#endif
