#ifndef CLASSES_CLOUD_CLOUDDATAMAN_H
#define CLASSES_CLOUD_CLOUDDATAMAN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace cloud {
// table 0x7100B7A2A0
class CloudDataMan : public ::ml::IWorkEvent {
public:
    CloudDataMan();
    virtual ~CloudDataMan();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    bool isReadOk() const;

    unsigned char pad_8[0x68];  // CloudMan's constructor allocates 0x70
};
}  // namespace cloud

#endif
