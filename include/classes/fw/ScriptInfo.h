#ifndef CLASSES_FW_SCRIPTINFO_H
#define CLASSES_FW_SCRIPTINFO_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace fw {
// table 0x7100B42B78
class ScriptInfo : public ::ml::IWorkEvent {
public:
    virtual ~ScriptInfo();  // slot 0
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace fw

#endif
