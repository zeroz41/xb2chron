#ifndef CLASSES_CLOUD_CLOUDOBJSKY_H
#define CLASSES_CLOUD_CLOUDOBJSKY_H

#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"
#include "grlib/CGLibRenderTarget.h"
#include "mm/Vec3.h"

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
    grlib::CGLibRenderTarget m_target;   // 0xC8, renderDetailPoli draws to it, renderSkyPoli reads it ("detail")
    mm::Vec3 m_scroll;                   // 0x490, the SKY_1 uniform's (createSkyUniform), wrapped by updateParams
    mm::Vec3 m_detailScroll;             // 0x4A0, the SKY_2 uniform's first three floats
    float m_detailParam;                 // 0x4B0, the last CloudCalcParams::m_skyParam[2] (1.0f from the ctor)
    bool m_isFirst;                      // 0x4B4, true until updateParams has taken m_detailParam
    bool m_isTargetClear = true;         // 0x4B5, renderDetailPoli clears m_target first while set
    int m_targetSize;                    // 0x4B8, the CloudCalcParams::m_skyTexSize m_target was set up with
};

}  // namespace cloud

#endif
