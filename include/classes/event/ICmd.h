#ifndef CLASSES_EVENT_ICMD_H
#define CLASSES_EVENT_ICMD_H

namespace event {
// table none (its derived classes')
class ICmd {
public:
    class Param;
    virtual ~ICmd() {}  // slot 0
    virtual void init() {}  // slot 2
    virtual int update(event::ICmd::Param const&) = 0;  // slot 3
    virtual void term() {}  // slot 4
};
}  // namespace event

#endif
