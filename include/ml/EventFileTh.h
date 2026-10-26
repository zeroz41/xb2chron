#ifndef ML_EVENTFILETH_H
#define ML_EVENTFILETH_H

namespace ml {

class FileHandleTh;

// what a file thread hands an ml::IWorkEvent's OnFileEvent (no table: its first word is the event's kind;
// fw::LocalizeResource::OnFileEvent takes 9 for its checked file's answer, fw::ScriptInfo::OnFileEvent 2 for a
// finished read). The names of the fields are not the original's.
class EventFileTh {
public:
    // hands over the read's data (the receiver frees it)
    void* moveFileData();
    int m_kind;
    unsigned char pad_4[0x4];
    FileHandleTh* m_handle;  // the read's (DevFileTh::readFile returned it)
    unsigned char pad_10[0x20];
    int m_result;  // nonzero when a read succeeded (fw::ScriptInfo::OnFileEvent)
};

}  // namespace ml

#endif
