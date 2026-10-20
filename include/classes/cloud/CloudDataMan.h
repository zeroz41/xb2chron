#ifndef CLASSES_CLOUD_CLOUDDATAMAN_H
#define CLASSES_CLOUD_CLOUDDATAMAN_H

#include "classes/cloud/CloudShaderMan.h"

namespace ml { class EventFileTh; }

namespace cloud {
// table 0x7100B7A2A0
class CloudDataMan : public ::cloud::CloudShaderMan {
public:
    virtual ~CloudDataMan();  // slot 0
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace cloud

#endif
