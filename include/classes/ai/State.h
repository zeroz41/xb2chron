#ifndef CLASSES_AI_STATE_H
#define CLASSES_AI_STATE_H

namespace ai { class State; }

namespace ai {
// table none (its derived classes')
class State {
public:
    virtual ~State();  // slot 0
    virtual void getName() const = 0;  // slot 2
    virtual void onEnter(void*, ai::State*) = 0;  // slot 3
    virtual void onLeave(void*, ai::State*) = 0;  // slot 4
    virtual void onStep(void*, void const*) = 0;  // slot 5
    virtual void onEvent(void*, void*);  // slot 6
    unsigned char pad_8[0x10];  // fields: size from its derived classes
};
}  // namespace ai

#endif
