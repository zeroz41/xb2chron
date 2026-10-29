#ifndef CLASSES_ML_FILEHANDLETH_H
#define CLASSES_ML_FILEHANDLETH_H

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
    unsigned char pad_2c[0x4];
    unsigned long m_userValue;  // copied to FileResTh's m_userValue
    unsigned char pad_38[0x5C];
    // 0x94: the file's path (DevFileReaderTh::asyncUpdate passes it to PathUtil::getFilePtrFromPath); its length is
    // not known: it runs to the next known field
    char m_path[0x12C];
    unsigned long m_timeStamp;  // copied to FileResTh's m_timeStamp
    unsigned long m_extra;  // copied to FileResTh's m_extra
    unsigned char pad_1d0[0x18];
    int m_state;  // 0x1E8 (DevFileReaderTh::asyncUpdate: 2 read, 4 failed or canceled)
    unsigned char pad_1ec[0x11];
    bool m_canceled;  // 0x1FD (stored atomically when a canceled read ends)
    bool m_failed;    // 0x1FE (stored atomically when no medium could read the file)
    bool m_done;      // 0x1FF (stored atomically when a medium read the file)
};
}  // namespace ml

#endif
