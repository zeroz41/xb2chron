#ifndef CLASSES_CLOUD_CLOUDOBJPLANE_H
#define CLASSES_CLOUD_CLOUDOBJPLANE_H

#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"
#include "mm/Vec3.h"

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
    // per plane, passed to createColorUniform in this order; the constructor zeroes them
    mm::Vec3 m_color0[2];  // 0x170
    mm::Vec3 m_color1[2];  // 0x190
    mm::Vec3 m_color2[2];  // 0x1B0
    mm::Vec3 m_color3[2];  // 0x1D0
    mm::Vec3 m_color4[2];  // 0x1F0
    float m_planeParam0;  // 0x210, 0 from the constructor (name inferred)
    float m_planeParam1;  // 0x214, 0.5 from the constructor (name inferred)
    bool m_planeFlag;  // 0x218, true from the constructor, updateParams reads it (name inferred)
    float m_farDist;  // 0x21C, plane 0's createDefUniform distance when not 0 (20000 otherwise)
    unsigned int m_uniParam;  // 0x220, passed to createDefUniform/createColorUniform
    // per plane, 1 from the constructor
    float m_scale0[2];  // 0x224
    float m_scale1[2];  // 0x22C
    float m_scale2[2];  // 0x234
    float m_scale3[2];  // 0x23C
    bool m_plane1CountSkip;  // 0x244, renderDepth draws plane 1 like a skipped plane 0 while set
    float m_uniRate;  // 0x248, last argument of createDefUniform/createColorUniform
};

}  // namespace cloud

#endif
