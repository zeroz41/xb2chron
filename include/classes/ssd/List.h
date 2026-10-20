// not proven yet: its table differs from the original's (word 2: _ZN3ssd4ListINS_11VoiceHandleEED1Ev where the original has _ZN3ssd4ListINS_11VoiceHandleEED0Ev)
#ifndef CLASSES_SSD_LIST_H
#define CLASSES_SSD_LIST_H

namespace ssd {
// a template: 9 instances in the module
template <typename T0>
class List {
public:
    virtual ~List();  // slot 0
};
}  // namespace ssd

#endif
