#ifndef CLASSES_CLOUD_CLOUDOBJ_H
#define CLASSES_CLOUD_CLOUDOBJ_H

namespace cloud {
// table 0x7100B7A118
class CloudObj {
public:
    virtual ~CloudObj() {}  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void alphaRender() = 0;  // slot 3
    virtual void alphaRenderSec() {}  // slot 4
};
}  // namespace cloud

#endif
