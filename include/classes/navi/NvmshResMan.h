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
};
}  // namespace navi

#endif
