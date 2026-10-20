#ifndef CLASSES_EVENT_CMDQUEUE_H
#define CLASSES_EVENT_CMDQUEUE_H

namespace event {
// a template: 4 instances in the module
template <unsigned long T0, int T1>
class CmdQueue {
public:
    virtual ~CmdQueue();  // slot T1
};
}  // namespace event

#endif
