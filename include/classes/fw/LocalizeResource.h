#ifndef CLASSES_FW_LOCALIZERESOURCE_H
#define CLASSES_FW_LOCALIZERESOURCE_H

#include "classes/fw/CommonResource.h"
#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace fw {
// table 0x7100B429B8
class LocalizeResource : public ::fw::CommonResource, public ::ml::IWorkEvent {
public:
    virtual ~LocalizeResource();  // slot 0
    virtual void update();  // slot 2
    virtual void getAssetName() const;  // slot 4
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 5
};
}  // namespace fw

#endif
