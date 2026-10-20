#ifndef CLASSES_CLOUD_CLOUDOBJPLANE_H
#define CLASSES_CLOUD_CLOUDOBJPLANE_H

namespace cloud {
// table 0x7100B7A1E8
class CloudObjPlane {
public:
    virtual ~CloudObjPlane();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
    virtual void alphaRenderSec();  // slot 4
};
}  // namespace cloud

#endif
