#ifndef CLASSES_FW_RENDERRESOURCE_H
#define CLASSES_FW_RENDERRESOURCE_H

#include "classes/fw/CommonResource.h"

namespace fw {
// table 0x7100B42A48
class RenderResource : public ::fw::CommonResource {
public:
    virtual ~RenderResource();  // slot 0
};
}  // namespace fw

#endif
