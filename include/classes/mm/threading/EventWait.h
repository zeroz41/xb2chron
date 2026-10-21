#ifndef CLASSES_MM_THREADING_EVENTWAIT_H
#define CLASSES_MM_THREADING_EVENTWAIT_H

namespace mm { namespace threading {
// table 0x7100B75998
class EventWait {
public:
    EventWait(bool signaled, bool manualClear);
    virtual ~EventWait();  // slot 0
    void finalize();
    void setSignal(bool signal);
    bool waitSignal(unsigned int milliseconds);
    bool isSignal() const;

    unsigned char pad_8[0x58];  // its nn::os event, the critical section guarding it, a flag
};
}}  // namespace mm::threading

#endif
