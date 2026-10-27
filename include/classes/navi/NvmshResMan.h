#ifndef CLASSES_NAVI_NVMSHRESMAN_H
#define CLASSES_NAVI_NVMSHRESMAN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

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

    unsigned char pad_8[0x169C];
    // bit 2: NvmshAcMan::objectUpdate clears every active object's status bits; the name is not the original's
    unsigned char m_flags;
    unsigned char pad_16A5[0x33];
    // the access objects' work buffer: m_acWorkNum ints for each of NvmshAcMan's 256 objects and its global one
    // (NvmshAcMan's constructor slices it); the names are not the original's
    int* m_acWork;
    unsigned char pad_16E0[0x4];
    int m_acWorkNum;
};
}  // namespace navi

#endif
