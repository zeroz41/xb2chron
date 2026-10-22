#ifndef ML_EVENTFILETH_H
#define ML_EVENTFILETH_H

namespace ml {

// what a file thread hands an ml::IWorkEvent's OnFileEvent (no table: its first word is the event's kind;
// fw::LocalizeResource::OnFileEvent takes 9 for its checked file's answer). The name of the field is not the
// original's.
class EventFileTh {
public:
    int m_kind;
};

}  // namespace ml

#endif
