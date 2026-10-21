#ifndef CLASSES_ML_DEVFILEACCESSOR_H
#define CLASSES_ML_DEVFILEACCESSOR_H

namespace ml { class DevFileParamTh; }
namespace ml { class DevFileResult; }
namespace ml { class FileHandleTh; }
namespace mm { class VAL64; }
namespace mtl { class ALLOC_HANDLE; }

namespace ml {
// table none (its derived classes')
class DevFileAccessor {
public:
    virtual ~DevFileAccessor();  // slot 0
    virtual void initialize() = 0;  // slot 2
    virtual void finalize() = 0;  // slot 3
    virtual void tail() = 0;  // slot 4
    virtual void addressAlignment() = 0;  // slot 5
    virtual bool isValid() const { return true; }  // slot 6
    virtual bool readBlock(ml::FileHandleTh*, char const*) { return false; }  // slot 7
    virtual void readBlockSlice(ml::FileHandleTh*, char const*, void*, unsigned int) = 0;  // slot 8
    virtual void getFileSize(char const*, mm::VAL64*, char const*) = 0;  // slot 9
    virtual void writeBlock(ml::FileHandleTh*, ml::DevFileResult&);  // slot 10
    virtual void createLoader(mtl::ALLOC_HANDLE) = 0;  // slot 11
    virtual void createWriter(mtl::ALLOC_HANDLE) = 0;  // slot 12
    virtual void createFileValid(mtl::ALLOC_HANDLE) = 0;  // slot 13
    virtual void rfOpen(ml::FileHandleTh*, char const*) = 0;  // slot 14
    virtual void rfRead(ml::FileHandleTh*, ml::DevFileParamTh const&) = 0;  // slot 15
    virtual void rfIsBusy(ml::FileHandleTh*) = 0;  // slot 16
    virtual void rfClose(ml::FileHandleTh*) = 0;  // slot 17
    virtual void rfIsUsedChannel(unsigned int) = 0;  // slot 18
    virtual void getFilesBlock(char*&, int&, mtl::ALLOC_HANDLE, char const*, char const*) = 0;  // slot 19
    virtual bool deleteFileBlock(char const*) { return false; }  // slot 20
};
}  // namespace ml

#endif
