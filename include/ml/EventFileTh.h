#ifndef ML_EVENTFILETH_H
#define ML_EVENTFILETH_H

namespace mm { namespace mtl { class IAllocator; } }

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
    // 0x10-0x28 and 0x38: copied from the handle's 0x2C, allocator, path, data and 0x68 (DevFileNxTh::tail)
    int pad_10;
    unsigned char pad_14[0x4];
    mm::mtl::IAllocator* m_allocator;
    const char* m_path;
    void* m_data;
    int m_result;  // nonzero when a read succeeded (fw::ScriptInfo::OnFileEvent; DevFileNxTh::tail passes the size)
    unsigned char pad_34[0x4];
    unsigned long pad_38;
};

}  // namespace ml

#endif
