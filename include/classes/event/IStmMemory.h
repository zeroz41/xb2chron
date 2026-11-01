#ifndef CLASSES_EVENT_ISTMMEMORY_H
#define CLASSES_EVENT_ISTMMEMORY_H

namespace mm { template <typename> class Rect; }

namespace event {
// table none (its derived classes')
class IStmMemory {
public:
    // inline and empty: StmPackMemory's destructor calls no base destructor
    virtual ~IStmMemory() {}  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void render(mm::Rect<int> const&, float) = 0;  // slot 3
    virtual void tail() {}  // slot 4
    // the region of the named stream and its size (StmPackMemory::adr; MotstmManager::adr calls it)
    virtual void* adr(char const*, unsigned long*) = 0;  // slot 5
    virtual void free(void*, int) = 0;  // slot 6
};
}  // namespace event

#endif
