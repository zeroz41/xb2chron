#ifndef CLASSES_FW_ICOLIEVENTLISTENER_H
#define CLASSES_FW_ICOLIEVENTLISTENER_H

namespace fw {
// table none (its derived classes')
class IColiEventListener {
public:
    class EnterInfo;
    class LeaveInfo;
    virtual void enter(fw::IColiEventListener::EnterInfo const&) = 0;  // slot 0
    virtual void leave(fw::IColiEventListener::LeaveInfo const&) = 0;  // slot 1
    virtual void contact(fw::IColiEventListener::EnterInfo const&);  // slot 2
};
}  // namespace fw

#endif
