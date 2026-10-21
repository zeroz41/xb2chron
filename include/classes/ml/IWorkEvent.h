#ifndef CLASSES_ML_IWORKEVENT_H
#define CLASSES_ML_IWORKEVENT_H

namespace ml { class EventFileTh; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B78200
class IWorkEvent {
public:
    virtual ~IWorkEvent() {}  // slot 0
    virtual void OnSystemPause(unsigned int) {}  // slot 2
    virtual void OnShutdownForce() {}  // slot 3
    virtual bool IsShutdownForce() { return true; }  // slot 4
    virtual void OnPauseTrigger(bool, char const*) {}  // slot 5
    virtual void OnViewResize(ml::EventView*) {}  // slot 6
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace ml

#endif
