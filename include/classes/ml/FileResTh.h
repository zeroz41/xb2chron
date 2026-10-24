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
    // whether the read started (fw::BdatManager::Impl's loadBdat and reloadBdat test the result)
    virtual bool loadBlock(mtl::ALLOC_HANDLE, char const*, unsigned int, unsigned int);  // slot 6
    virtual void loadBlock(mm::mtl::IAllocator*, char const*, unsigned int);  // slot 7
    virtual bool load(mtl::ALLOC_HANDLE, char const*, unsigned int, ml::FILE_PRIO);  // slot 8
    virtual void load(mm::mtl::IAllocator*, char const*, unsigned int, ml::FILE_PRIO);  // slot 9
    virtual void release();  // slot 10
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 11
    // whether its file's data is there (the data pointer is set)
    bool isExist() const;

    // the names are not the original's
    void* m_handle;  // set while the file is being read (fw::SoundResource::update waits for it to clear)
    void* m_data;  // the file's data (isExist tests it)
    int m_size;  // the data's size; -2 when there is no file (fw::SoundResource::update skips the data then)
    unsigned char pad_d4[0xC];
    // handed to fw::AssetData::AssignFromMemory's last parameter with the data (fw::CommonResource::update), where
    // CommonResource::updateBlock hands it what DevFileTh::readFileBlock returned through its VAL64 (the name is
    // not the original's; 1.0.0's CommonResource has a getAssetTimeStamp)
    unsigned long m_timeStamp;
    unsigned char pad_e8[0x8];
    bool m_ownsData;  // cleared when fw::AssetData::AssignFromMemory takes the data over
};
}  // namespace ml

#endif
