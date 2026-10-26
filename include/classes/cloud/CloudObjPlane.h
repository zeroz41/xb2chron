#ifndef CLASSES_CLOUD_CLOUDOBJPLANE_H
#define CLASSES_CLOUD_CLOUDOBJPLANE_H

#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"

namespace cloud {

// table 0x7100B7A1E8. Member names are not the original's.
class CloudObjPlane : public ::cloud::CloudObj {
public:
    CloudObjPlane();
    virtual ~CloudObjPlane();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
    virtual void alphaRenderSec();  // slot 4
    void updateSide();
    void updateParams();
    void updateUniform();
    void renderPlanePoli(unsigned int idx);
    void renderBlur(unsigned int idx);
    void renderDepth(unsigned int idx);
    void renderLastPoli(unsigned int idx);
    void renderPlaneDef();

    // one of each per plane (the constructor creates them in pairs, plane by plane)
    CloudUniform m_planeUniform0[2];  // 0x20, CLOUD_UNIFORM_DEF
    CloudUniform m_planeUniform1[2];  // 0x90, CLOUD_UNIFORM_COLOR
    CloudUniform m_planeUniform2;  // 0x100, CLOUD_UNIFORM_BLUR
    CloudUniform m_planeUniform3;  // 0x138, CLOUD_UNIFORM_BLUR
};

}  // namespace cloud

#endif
