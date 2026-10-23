#ifndef CLASSES_FW_ICOLIEVENTLISTENER_H
#define CLASSES_FW_ICOLIEVENTLISTENER_H

namespace fw { class ColiObject; }

namespace fw {
// table none (its derived classes')
class IColiEventListener {
public:
    // an event between two collision objects (GfComCollider's handlers read the other one; the names are not
    // the original's)
    class EnterInfo {
    public:
        fw::ColiObject* m_self;
        fw::ColiObject* m_other;
    };
    class LeaveInfo {
    public:
        fw::ColiObject* m_self;
        fw::ColiObject* m_other;
    };
    virtual void enter(fw::IColiEventListener::EnterInfo const&) = 0;  // slot 0
    virtual void leave(fw::IColiEventListener::LeaveInfo const&) = 0;  // slot 1
    virtual void contact(fw::IColiEventListener::EnterInfo const&);  // slot 2
};
}  // namespace fw

#endif
