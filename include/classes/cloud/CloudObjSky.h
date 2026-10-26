#ifndef CLASSES_CLOUD_CLOUDOBJSKY_H
#define CLASSES_CLOUD_CLOUDOBJSKY_H

#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"
#include "grlib/CGLibRenderTarget.h"

namespace cloud {

// table 0x7100B7A220. Member names are not the original's.
class CloudObjSky : public ::cloud::CloudObj {
public:
    CloudObjSky();
    virtual ~CloudObjSky();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
    void updateParams();
    void updateUniform();
    void renderDetailPoli();
    void renderSkyPoli();
    void renderLastPoli();

    CloudUniform m_skyUniform0;          // 0x20, CLOUD_UNIFORM_SKY_0
    CloudUniform m_skyUniform1;          // 0x58, CLOUD_UNIFORM_SKY_1
    CloudUniform m_skyUniform2;          // 0x90, CLOUD_UNIFORM_SKY_2
    grlib::CGLibRenderTarget m_target;   // 0xC8
};

}  // namespace cloud

#endif
