#ifndef CLASSES_ML_FILEHANDLETH_H
#define CLASSES_ML_FILEHANDLETH_H

namespace mm { namespace mtl { class IAllocator; } }
namespace ml { class IWorkEvent; }

namespace ml {
// a file request of the file thread (DevFileTh::readFile returns one). Only the fields FileResTh::OnFileEvent reads
// are known; their names are not the original's
class FileHandleTh {
public:
    // hands over the read's data, clearing it (EventFileTh::moveFileData, FileResTh::OnFileEvent; the name is not the
    // original's)
    void* moveData() {
        void* data = m_data;
        m_data = nullptr;
        return data;
    }

    unsigned char pad_0[0x8];
    void* m_data;  // the read's data (OnFileEvent takes it over and clears it)
    unsigned char pad_10[0x8];
    int m_size;  // the data's size
    unsigned char pad_1c[0xC];
    int m_readSize;  // 0x28 (DevFileReaderTh::asyncUpdate clears it before each medium's read)
    int pad_2c;  // passed on in the read's end event (DevFileNxTh::tail)
    // copied to FileResTh's m_allocator (FileResTh::release frees the data through it when set)
    mm::mtl::IAllocator* m_allocator;
    unsigned char pad_38[0x28];
    // 0x60: who hears the read's end (FileResTh::release clears it before canceling the read)
    IWorkEvent* m_listener;
    unsigned long pad_68;  // passed on in the read's end event (DevFileNxTh::tail)
    // 0x70, 0x78: where the read's end hands its data and size when set (DevFileNxTh::tail; the names are not the
    // original's)
    void** m_outData;
    int* m_outSize;
    unsigned char pad_80[0x14];
    // 0x94: the file's path (DevFileReaderTh::asyncUpdate passes it to PathUtil::getFilePtrFromPath); its length is
    // not known: it runs to the next known field
    char m_path[0x12C];
    unsigned long m_timeStamp;  // copied to FileResTh's m_timeStamp
    unsigned long m_extra;  // copied to FileResTh's m_extra
    unsigned char pad_1d0[0x4];
    // 0x1D4: the read channel it holds (DevFileNxTh::rfOpen/rfClose index their Impl's channels with it; the name is
    // not the original's)
    unsigned int m_channel;
    unsigned char pad_1d8[0x10];
    int m_state;  // 0x1E8 (DevFileReaderTh::asyncUpdate: 2 read, 4 failed or canceled)
    unsigned char pad_1ec[0x11];
    bool m_canceled;  // 0x1FD (stored atomically when a canceled read ends)
    bool m_failed;    // 0x1FE (stored atomically when no medium could read the file)
    bool m_done;      // 0x1FF (stored atomically when a medium read the file)
};
}  // namespace ml

#endif
