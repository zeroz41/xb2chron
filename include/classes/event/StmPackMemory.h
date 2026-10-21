#ifndef CLASSES_EVENT_STMPACKMEMORY_H
#define CLASSES_EVENT_STMPACKMEMORY_H

#include "classes/event/IStmMemory.h"

namespace mm { template <typename> class Rect; }

namespace event {
// table 0x7100B3C470
class StmPackMemory : public ::event::IStmMemory {
public:
    virtual ~StmPackMemory();  // slot 0
    virtual void update();  // slot 2
    virtual void render(mm::Rect<int> const&, float);  // slot 3
    virtual void adr(char const*, unsigned long*);  // slot 5
    virtual void free(void*, int);  // slot 6
    virtual bool isLoadingPrio(float) const;  // slot 7
    virtual void isFailure() const;  // slot 8
};
}  // namespace event

#endif
