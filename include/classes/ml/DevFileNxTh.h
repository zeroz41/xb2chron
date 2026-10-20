#ifndef CLASSES_ML_DEVFILENXTH_H
#define CLASSES_ML_DEVFILENXTH_H

#include "classes/ml/DevFileAccessor.h"

namespace ml { class DevFileParamTh; }
namespace ml { class DevFileResult; }
namespace ml { class FileHandleTh; }
namespace mm { class VAL64; }
namespace mtl { class ALLOC_HANDLE; }

namespace ml {
// a base of ml::DevFileNxTh no evidence names yet
class TUnk_B76BA0 {
public:
    virtual ~TUnk_B76BA0();
};
// table 0x7100B76AE0; base at 0x8 unknown (TUnk_B76BA0)
class DevFileNxTh : public ::ml::DevFileAccessor, public TUnk_B76BA0 {
public:
    virtual ~DevFileNxTh();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void tail();  // slot 4
    virtual void addressAlignment();  // slot 5
    virtual void readBlock(ml::FileHandleTh*, char const*);  // slot 7
    virtual void readBlockSlice(ml::FileHandleTh*, char const*, void*, unsigned int);  // slot 8
    virtual void getFileSize(char const*, mm::VAL64*, char const*);  // slot 9
    virtual void writeBlock(ml::FileHandleTh*, ml::DevFileResult&);  // slot 10
    virtual void createLoader(mtl::ALLOC_HANDLE);  // slot 11
    virtual void createWriter(mtl::ALLOC_HANDLE);  // slot 12
    virtual void createFileValid(mtl::ALLOC_HANDLE);  // slot 13
    virtual void rfOpen(ml::FileHandleTh*, char const*);  // slot 14
    virtual void rfRead(ml::FileHandleTh*, ml::DevFileParamTh const&);  // slot 15
    virtual void rfIsBusy(ml::FileHandleTh*);  // slot 16
    virtual void rfClose(ml::FileHandleTh*);  // slot 17
    virtual void rfIsUsedChannel(unsigned int);  // slot 18
    virtual void getFilesBlock(char*&, int&, mtl::ALLOC_HANDLE, char const*, char const*);  // slot 19
    virtual void deleteFileBlock(char const*);  // slot 20
    virtual void getMediaRootPath() const;  // slot 21
};
}  // namespace ml

#endif
