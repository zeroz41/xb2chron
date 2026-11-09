#ifndef CLASSES_ML_DEVFILEARCHIVENX_H
#define CLASSES_ML_DEVFILEARCHIVENX_H

#include "classes/ml/DevFileAccessor.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ml/CriticalSection.h"
#include "nn/fs.h"
#include "ml/OpenReadParam.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedObjectAllocator.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/UniquePtr.h"
#include "mtl/MemManager.h"

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
    virtual int addressAlignment() { return 0x10; }  // slot 5 (weak: the original keeps it with the inline slots)
    virtual bool readBlockSlice(ml::FileHandleTh*, char const*, void*, unsigned int);  // slot 8
    virtual int getFileSize(char const*, mm::VAL64*, char const*);  // slot 9
    virtual ml::DevFileJobTh* createLoader(mtl::ALLOC_HANDLE);  // slot 11
    virtual ml::DevFileWriterTh* createWriter(mtl::ALLOC_HANDLE);  // slot 12
    virtual ml::DevFileJobTh* createFileValid(mtl::ALLOC_HANDLE);  // slot 13
    virtual bool rfOpen(ml::FileHandleTh*, char const*);  // slot 14
    virtual bool rfRead(ml::FileHandleTh*, ml::DevFileParamTh const&);  // slot 15
    virtual bool rfIsBusy(ml::FileHandleTh*);  // slot 16
    virtual bool rfClose(ml::FileHandleTh*);  // slot 17
    virtual bool rfIsUsedChannel(unsigned int);  // slot 18
    virtual bool getFilesBlock(char*&, int&, mtl::ALLOC_HANDLE, char const*, char const*);  // slot 19
    virtual const char* getMediaRootPath() const;  // slot 21

    DevFileArchiveNx(mtl::ALLOC_HANDLE handle);

    // named by the symbols: a read channel's thread entry (arg is its OpenReadParam); waits for DevFileTh's setup,
    // then runs thUpdate
    static unsigned int thFileLoader(void* arg);
    // named by the symbols: a read channel's loop; thFileLoader calls it with no object set up, so it reads only its
    // argument
    void thUpdate(void* arg);
    // named by the symbols: turns '\\' into '/', adds a leading '/' and lowercases the last path element (when it is
    // plain ASCII); rfOpen calls it with no object set up
    void normalizeFileName(mm::mtl::FixStr<256>& name);

    // the device's state (0x2A48), built by the constructor with the handle it is given; DevFileNxTh::Impl's
    // members first
    struct Param {
        // a thread's file (0x118; Param::finalize closes m_file; the names are not the original's)
        struct ThreadFile {
            unsigned long pad_0;
            nn::fs::FileHandle m_file;  // 0x8
            unsigned char pad_10[0x108];
        };

        void finalize();
        void addThreadFilehandle(unsigned long, mm::mtl::FixStr<256> const&);

        mm::mtl::FixedArray<OpenReadParam, 13> m_params;  // the read channels
        bool pad_17F8;  // stored atomically
        int pad_17FC;  // stored atomically
        CriticalSection m_cs;
        mm::mtl::FixedObjectAllocator<ThreadFile, 16> m_threadFiles;  // the names are not the original's
        mm::mtl::FixedQueue<ThreadFile*, 16> m_threadFileQueue;
    };

    unsigned char pad_10[4];
    mtl::ALLOC_HANDLE m_alloc;  // the handle the constructor is given (the name is not the original's)
    int pad_18;
    mm::mtl::UniquePtr<Param> m_impl;
};
}  // namespace ml

#endif
