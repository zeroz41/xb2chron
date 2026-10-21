#ifndef CLASSES_EVENT_ITODO_H
#define CLASSES_EVENT_ITODO_H

namespace event { class Param; }

namespace event {
// table none (its derived classes')
class ITodo {
public:
    virtual ~ITodo() {}  // slot 0
    virtual void cmdName() const = 0;  // slot 2
    virtual void doit(event::Param const&) = 0;  // slot 3
    virtual void undo(event::Param const&) {}  // slot 4
    virtual void redo(event::Param const&) {}  // slot 5
};
}  // namespace event

#endif
