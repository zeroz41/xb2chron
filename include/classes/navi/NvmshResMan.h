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
};
}  // namespace navi

#endif
