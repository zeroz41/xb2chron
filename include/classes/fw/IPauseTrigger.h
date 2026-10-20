#ifndef CLASSES_FW_IPAUSETRIGGER_H
#define CLASSES_FW_IPAUSETRIGGER_H

namespace fw {
// table 0x7100B41688
class IPauseTrigger {
public:
    virtual ~IPauseTrigger();  // slot 0
    virtual void enterPauseCallback();  // slot 2
    virtual void exitPauseCallback();  // slot 3
    virtual void updatePauseCallback();  // slot 4
    virtual void activate();  // slot 5
    virtual void deactivate();  // slot 6
};
}  // namespace fw

#endif
