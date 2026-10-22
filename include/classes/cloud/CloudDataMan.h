#ifndef CLASSES_CLOUD_CLOUDDATAMAN_H
#define CLASSES_CLOUD_CLOUDDATAMAN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace cloud {
// table 0x7100B7A2A0
class CloudDataMan : public ::ml::IWorkEvent {
public:
    virtual ~CloudDataMan();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace cloud

#endif
