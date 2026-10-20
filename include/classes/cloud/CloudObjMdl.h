#ifndef CLASSES_CLOUD_CLOUDOBJMDL_H
#define CLASSES_CLOUD_CLOUDOBJMDL_H

namespace cloud {
// table 0x7100B7A1B0
class CloudObjMdl {
public:
    virtual ~CloudObjMdl();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
    virtual void alphaRenderSec();  // slot 4
};
}  // namespace cloud

#endif
