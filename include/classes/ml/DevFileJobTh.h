#ifndef CLASSES_ML_DEVFILEJOBTH_H
#define CLASSES_ML_DEVFILEJOBTH_H

namespace ml {
class DevFileReaderTh;
class FileHandleTh;

// table 0x7100B776E0
class DevFileJobTh {
public:
    // DevFileNxTh::createLoader/createWriter and DevFileArchiveNx::createLoader inline it
    DevFileJobTh() : m_result(0), m_handle(nullptr), m_cancel(false) {}
    virtual ~DevFileJobTh() {}  // slot 0
    virtual bool asyncUpdate() { return true; }  // slot 2
    virtual int getJobType() const { return 0; }  // slot 3
    virtual DevFileReaderTh* getReader() { return nullptr; }  // slot 4

    // the names of these three are not the original's
    int m_result;            // the job's result: asyncUpdate stores 2 (found/read) or -1
    FileHandleTh* m_handle;  // the request the job works on (asyncUpdate reads its path, stores its state)
    bool m_cancel;           // set when the request is canceled (DevFileReaderTh::asyncUpdate stops on it)
};
}  // namespace ml

#endif
