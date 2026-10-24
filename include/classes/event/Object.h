#ifndef CLASSES_EVENT_OBJECT_H
#define CLASSES_EVENT_OBJECT_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3DBF0
class Object : public ::event::IBouCallback, public ::event::IManiCallback {
public:
    virtual ~Object();  // slot 0
    virtual void clear() {}  // slot 4
    virtual void start() {}  // slot 5
    virtual void end() {}  // slot 6
    virtual void update() {}  // slot 7
    virtual void render(mm::Col4 const&) {}  // slot 8
    virtual void tail() {}  // slot 9
    virtual bool isLoading() const { return false; }  // slot 10
    unsigned char pad_10[0x58];
};
}  // namespace event

#endif
