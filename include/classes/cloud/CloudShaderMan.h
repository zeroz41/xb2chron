#ifndef CLASSES_CLOUD_CLOUDSHADERMAN_H
#define CLASSES_CLOUD_CLOUDSHADERMAN_H

#include "classes/ml/IWorkEvent.h"

namespace cloud { class CloudShaderType; }

namespace cloud {
// table none (its derived classes')
class CloudShaderMan : public ::ml::IWorkEvent {
public:
    virtual ~CloudShaderMan();  // slot 0
    virtual void selectRenderPlane(cloud::CloudShaderType, unsigned int, unsigned int, unsigned int);  // slot 8
};
}  // namespace cloud

#endif
