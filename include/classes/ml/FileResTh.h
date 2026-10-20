#ifndef CLASSES_ML_FILERESTH_H
#define CLASSES_ML_FILERESTH_H

#include "classes/ml/BaseObjectM.h"
#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }
namespace ml { enum FILE_PRIO : int; }
namespace mm { namespace mtl { class IAllocator; }}
namespace mtl { class ALLOC_HANDLE; }

namespace ml {
// table 0x7100B76DB8
class FileResTh : public ::ml::BaseObjectM, public ::ml::IWorkEvent {
public:
    virtual ~FileResTh();  // slot 0
    virtual void setMem(void*, int, char const*, bool);  // slot 5
    virtual void loadBlock(mtl::ALLOC_HANDLE, char const*, unsigned int, unsigned int);  // slot 6
    virtual void loadBlock(mm::mtl::IAllocator*, char const*, unsigned int);  // slot 7
    virtual void load(mtl::ALLOC_HANDLE, char const*, unsigned int, ml::FILE_PRIO);  // slot 8
    virtual void load(mm::mtl::IAllocator*, char const*, unsigned int, ml::FILE_PRIO);  // slot 9
    virtual void release();  // slot 10
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 11
};
}  // namespace ml

#endif
