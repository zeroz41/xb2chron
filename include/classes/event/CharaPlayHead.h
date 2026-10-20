#ifndef CLASSES_EVENT_CHARAPLAYHEAD_H
#define CLASSES_EVENT_CHARAPLAYHEAD_H

namespace event {
// table 0x7100B3E5A0
class CharaPlayHead {
public:
    virtual ~CharaPlayHead();  // slot 0
    virtual void init();  // slot 2
    virtual void vf3();  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
