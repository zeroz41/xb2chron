#ifndef CLASSES_CLOUD_CLOUDOBJSKY_H
#define CLASSES_CLOUD_CLOUDOBJSKY_H

#include "classes/cloud/CloudObj.h"

namespace cloud {
// table 0x7100B7A220
class CloudObjSky : public ::cloud::CloudObj {
public:
    virtual ~CloudObjSky();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
};
}  // namespace cloud

#endif
