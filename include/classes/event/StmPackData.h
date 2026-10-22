#ifndef CLASSES_EVENT_STMPACKDATA_H
#define CLASSES_EVENT_STMPACKDATA_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace event {
// table 0x7100B3C420
class StmPackData : public ::ml::IWorkEvent {
public:
    virtual ~StmPackData();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace event

#endif
