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
};
}  // namespace event

#endif
