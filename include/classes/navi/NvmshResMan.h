#ifndef CLASSES_NAVI_NVMSHRESMAN_H
#define CLASSES_NAVI_NVMSHRESMAN_H

#include "classes/ml/IWorkEvent.h"
#include "navi/NvmshResData.h"

namespace ml { class EventFileTh; }
namespace ml { class FileHandleTh; }

namespace navi {
// table 0x7100B7F7E0
class NvmshResMan : public ::ml::IWorkEvent {
public:
    virtual ~NvmshResMan();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    void setupResource(const unsigned char* resource, const char* name);
    void releaseResource();
    // NvmshManager::jobUpdate's per-frame step
    void update();
    void tail();
    void resourceNaviUpdate();

    // the resource reads in flight (OnFileEvent clears the finished one and its m_flags bit 0x10000 << index),
    // and what each read gives (the names are not the original's)
    ml::FileHandleTh* m_fileHandles[4];
    void* m_fileData[4];
    NvmshResMemMan* m_memMan;  // 0x48, the blocks of m_buffer (the name is not the original's)
    unsigned char pad_50[0x60];
    NvmshResData m_resData[26];  // 0xB0 (the name is not the original's)
    unsigned char pad_15D0[0xD4];
    // bit 2: NvmshAcMan::objectUpdate clears every active object's status bits, bit 4: a resource block was
    // marked by update, bit 5: skip one resourceNaviUpdate, bits 16-19: reads in flight; the name is not the
    // original's
    unsigned int m_flags;
    unsigned char* m_buffer;  // 0x16A8, the constructor's allocation (the name is not the original's)
    unsigned char pad_16B0[0x28];
    // the access objects' work buffer: m_acWorkNum ints for each of NvmshAcMan's 256 objects and its global one
    // (NvmshAcMan's constructor slices it); the names are not the original's
    int* m_acWork;
    unsigned char pad_16E0[0x4];
    int m_acWorkNum;
    unsigned char pad_16E8[0x2];
    // tail() flips m_writeBank and sets m_readBank to the other one (the names are not the original's)
    short m_readBank;
    short m_writeBank;
};
}  // namespace navi

#endif
