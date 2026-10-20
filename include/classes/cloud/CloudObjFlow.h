#ifndef CLASSES_CLOUD_CLOUDOBJFLOW_H
#define CLASSES_CLOUD_CLOUDOBJFLOW_H

#include "classes/cloud/CloudObj.h"

namespace cloud {
// table 0x7100B7A178
class CloudObjFlow : public ::cloud::CloudObj {
public:
    virtual ~CloudObjFlow();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
};
}  // namespace cloud

#endif
