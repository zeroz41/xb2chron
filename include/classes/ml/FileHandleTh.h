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
    unsigned char pad_1c[0x14];
    unsigned long m_userValue;  // copied to FileResTh's m_userValue
    unsigned char pad_38[0x188];
    unsigned long m_timeStamp;  // copied to FileResTh's m_timeStamp
    unsigned long m_extra;  // copied to FileResTh's m_extra
};
}  // namespace ml

#endif
