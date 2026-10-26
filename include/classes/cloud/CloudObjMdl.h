#ifndef CLASSES_CLOUD_CLOUDOBJMDL_H
#define CLASSES_CLOUD_CLOUDOBJMDL_H

#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"
#include "cloud/CloudMdlListMan.h"
#include "cloud/CloudMdlParts.h"

namespace cloud {

// table 0x7100B7A1B0. Member names are not the original's.
class CloudObjMdl : public ::cloud::CloudObj {
public:
    // inline: CloudObjMan::createMdl builds it in place (the symbols name no out-of-line copy)
    CloudObjMdl() {
        m_mdlUniform0.createUniform(CLOUD_UNIFORM_MDL_0, 1);
        m_mdlUniform.createUniform(CLOUD_UNIFORM_MDL, 1);
        m_scrollX = 0.0f;
        m_scrollY = 0.0f;
        m_scrollZ = 0.0f;
        m_param0 = 1.0f;
        m_param1 = 2.0f;
    }
    virtual ~CloudObjMdl();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
    virtual void alphaRenderSec();  // slot 4
    void updateUniform();
    void renderBaseMdlPoli();
    void renderLastPoli();
    void counterRender();

    CloudMdlListMan m_partsList;  // 0x20
    CloudUniform m_mdlUniform0;   // 0x30, CLOUD_UNIFORM_MDL_0
    CloudUniform m_mdlUniform;    // 0x68, CLOUD_UNIFORM_MDL ("U_MDL")
    // update sets it to (1, 1, 1) normalized, scaled by CloudMan's frame and rate and two CloudCalcParams values
    float m_scrollX;              // 0xA0
    float m_scrollY;              // 0xA4
    float m_scrollZ;              // 0xA8
    unsigned char pad_AC[0x4];
    float m_param0;               // 0xB0, 1.0f from the constructor (its use is not known)
    float m_param1;               // 0xB4, 2.0f from the constructor (its use is not known)
    unsigned char pad_B8[0x8];    // CloudObjMan::createMdl allocates 0xC0
};

}  // namespace cloud

#endif
