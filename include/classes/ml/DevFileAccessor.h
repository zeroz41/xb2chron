#ifndef CLASSES_ML_DEVFILEACCESSOR_H
#define CLASSES_ML_DEVFILEACCESSOR_H

namespace ml { class DevFileParamTh; }
namespace ml { enum DevFileResult : int; }  // an enum: writeBlock stores 0 through it as an int
namespace ml { class FileHandleTh; }
namespace ml { class DevFileJobTh; }
namespace ml { class DevFileReaderTh; }
namespace ml { class DevFileWriterTh; }
namespace mm { class VAL64; }
#include "mtl/AllocHandle.h"

namespace ml {
// table 0x7100B77620: every slot has a body (inline: the table and its slots are emitted where the derived
// classes' constructors store it). Return types follow the slots' bodies (create* return nullptr; the pointee
// classes are inferred from the slot names).
class DevFileAccessor {
public:
    virtual ~DevFileAccessor() {}  // slot 0
    virtual bool initialize() { return true; }  // slot 2
    virtual bool finalize() { return true; }  // slot 3
    virtual void tail() {}  // slot 4
    virtual int addressAlignment() { return 0x10; }  // slot 5
    virtual bool isValid() const { return true; }  // slot 6
    virtual bool readBlock(ml::FileHandleTh*, char const*) { return false; }  // slot 7
    virtual bool readBlockSlice(ml::FileHandleTh*, char const*, void*, unsigned int) { return false; }  // slot 8
    virtual int getFileSize(char const*, mm::VAL64*, char const*) { return -1; }  // slot 9
    virtual bool writeBlock(ml::FileHandleTh*, ml::DevFileResult& result) {  // slot 10
        result = DevFileResult();
        return false;
    }
    virtual ml::DevFileJobTh* createLoader(mtl::ALLOC_HANDLE) { return nullptr; }  // slot 11
    virtual ml::DevFileWriterTh* createWriter(mtl::ALLOC_HANDLE) { return nullptr; }  // slot 12
    virtual ml::DevFileJobTh* createFileValid(mtl::ALLOC_HANDLE) { return nullptr; }  // slot 13
    virtual bool rfOpen(ml::FileHandleTh*, char const*) { return false; }  // slot 14
    virtual bool rfRead(ml::FileHandleTh*, ml::DevFileParamTh const&) { return false; }  // slot 15
    virtual bool rfIsBusy(ml::FileHandleTh*) { return false; }  // slot 16
    virtual bool rfClose(ml::FileHandleTh*) { return false; }  // slot 17
    virtual bool rfIsUsedChannel(unsigned int) { return false; }  // slot 18
    virtual bool getFilesBlock(char*&, int&, mtl::ALLOC_HANDLE, char const*, char const*) { return false; }  // slot 19
    virtual bool deleteFileBlock(char const*) { return false; }  // slot 20
    virtual const char* getMediaRootPath() const { return ""; }  // slot 21
};
}  // namespace ml

#endif
