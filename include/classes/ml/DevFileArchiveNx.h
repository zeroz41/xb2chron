#ifndef CLASSES_ML_DEVFILEARCHIVENX_H
#define CLASSES_ML_DEVFILEARCHIVENX_H

#include "classes/ml/DevFileAccessor.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DevFileParamTh; }
namespace ml { class FileHandleTh; }
namespace mm { class VAL64; }
#include "mtl/AllocHandle.h"

namespace ml {
// table 0x7100B76BE0; base at 0x8 mm::mtl::PtrSingleton<DevFileArchiveNx> (the constructor stores its table there)
class DevFileArchiveNx : public ::ml::DevFileAccessor, public ::mm::mtl::PtrSingleton<DevFileArchiveNx> {
public:
    virtual ~DevFileArchiveNx();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual void tail();  // slot 4
    virtual int addressAlignment();  // slot 5
    virtual bool readBlockSlice(ml::FileHandleTh*, char const*, void*, unsigned int);  // slot 8
    virtual int getFileSize(char const*, mm::VAL64*, char const*);  // slot 9
    virtual ml::DevFileReaderTh* createLoader(mtl::ALLOC_HANDLE);  // slot 11
    virtual ml::DevFileWriterTh* createWriter(mtl::ALLOC_HANDLE);  // slot 12
    virtual ml::DevFileJobTh* createFileValid(mtl::ALLOC_HANDLE);  // slot 13
    virtual bool rfOpen(ml::FileHandleTh*, char const*);  // slot 14
    virtual bool rfRead(ml::FileHandleTh*, ml::DevFileParamTh const&);  // slot 15
    virtual bool rfIsBusy(ml::FileHandleTh*);  // slot 16
    virtual bool rfClose(ml::FileHandleTh*);  // slot 17
    virtual bool rfIsUsedChannel(unsigned int);  // slot 18
    virtual bool getFilesBlock(char*&, int&, mtl::ALLOC_HANDLE, char const*, char const*);  // slot 19
    virtual const char* getMediaRootPath() const;  // slot 21
};
}  // namespace ml

#endif
