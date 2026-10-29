#ifndef CLASSES_ML_DEVFILEJOBTH_H
#define CLASSES_ML_DEVFILEJOBTH_H

namespace ml {
class DevFileReaderTh;

// table 0x7100B776E0
class DevFileJobTh {
public:
    // DevFileNxTh::createLoader/createWriter and DevFileArchiveNx::createLoader inline it
    DevFileJobTh() : pad_008(0), pad_010(nullptr), pad_018(false) {}
    virtual ~DevFileJobTh() {}  // slot 0
    virtual bool asyncUpdate() { return true; }  // slot 2
    virtual int getJobType() const { return 0; }  // slot 3
    virtual DevFileReaderTh* getReader() { return nullptr; }  // slot 4

    int pad_008;   // the job's result: DevFileJobValidNxTh::asyncUpdate stores 2 (found) or -1
    void* pad_010; // DevFileJobValidNxTh::asyncUpdate reads a path at +0x94 and stores a state at +0x1E8
    bool pad_018;
};
}  // namespace ml

#endif
