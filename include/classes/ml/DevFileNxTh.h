#ifndef CLASSES_ML_DEVFILENXTH_H
#define CLASSES_ML_DEVFILENXTH_H

#include "classes/ml/DevFileAccessor.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ml/CriticalSection.h"
#include "ml/OpenReadParam.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/UniquePtr.h"
#include "mtl/MemManager.h"

namespace ml { class DevFileParamTh; }
namespace ml { enum DevFileResult : int; }  // an enum: writeBlock stores 0 through it as an int
namespace ml { class FileHandleTh; }
namespace mm { class VAL64; }

namespace ml {
// table 0x7100B76AE0; base at 0x8 mm::mtl::PtrSingleton<DevFileNxTh> (the constructor stores its table there)
class DevFileNxTh : public ::ml::DevFileAccessor, public ::mm::mtl::PtrSingleton<DevFileNxTh> {
public:
    virtual ~DevFileNxTh();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual void tail();  // slot 4
    virtual int addressAlignment();  // slot 5
    virtual bool readBlock(ml::FileHandleTh*, char const*);  // slot 7
    virtual bool readBlockSlice(ml::FileHandleTh*, char const*, void*, unsigned int);  // slot 8
    virtual int getFileSize(char const*, mm::VAL64*, char const*);  // slot 9
    virtual bool writeBlock(ml::FileHandleTh*, ml::DevFileResult&);  // slot 10
    virtual ml::DevFileJobTh* createLoader(mtl::ALLOC_HANDLE);  // slot 11
    virtual ml::DevFileWriterTh* createWriter(mtl::ALLOC_HANDLE);  // slot 12
    virtual ml::DevFileJobTh* createFileValid(mtl::ALLOC_HANDLE);  // slot 13
    virtual bool rfOpen(ml::FileHandleTh*, char const*);  // slot 14
    virtual bool rfRead(ml::FileHandleTh*, ml::DevFileParamTh const&);  // slot 15
    virtual bool rfIsBusy(ml::FileHandleTh*);  // slot 16
    virtual bool rfClose(ml::FileHandleTh*);  // slot 17
    virtual bool rfIsUsedChannel(unsigned int);  // slot 18
    virtual bool getFilesBlock(char*&, int&, mtl::ALLOC_HANDLE, char const*, char const*);  // slot 19
    virtual bool deleteFileBlock(char const*);  // slot 20
    virtual const char* getMediaRootPath() const;  // slot 21

    DevFileNxTh(mtl::ALLOC_HANDLE handle);

    // what the constructor allocates (0x1828 bytes, value-initialized); the field names are inferred
    struct Impl {
        mm::mtl::FixedArray<OpenReadParam, 13> m_params;  // the read channels (rfIsUsedChannel indexes them)
        bool pad_17F8;  // stored atomically
        int pad_17FC;  // stored atomically
        CriticalSection m_cs;
    };

    unsigned char pad_10[4];
    mtl::ALLOC_HANDLE m_alloc;  // the handle the constructor is given (the name is not the original's)
    int pad_18;
    mm::mtl::UniquePtr<Impl> m_impl;
};
}  // namespace ml

#endif
