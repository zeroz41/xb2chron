#ifndef CLASSES_CLOUD_CLOUDOBJFLOW_H
#define CLASSES_CLOUD_CLOUDOBJFLOW_H

#include "classes/cloud/CloudObj.h"
#include "cloud/CloudUniform.h"

namespace cloud {

// table 0x7100B7A178. Member names are not the original's.
class CloudObjFlow : public ::cloud::CloudObj {
public:
    // inline: CloudObjMan::createFlow builds it in place (the symbols name no out-of-line copy)
    CloudObjFlow() {
        m_flowUniform.createUniform(CLOUD_UNIFORM_FLOW_0, 1);
        m_flowUniform2.createUniform(CLOUD_UNIFORM_FLOW_1, 1);
    }
    virtual ~CloudObjFlow();  // slot 0
    virtual void update();  // slot 2
    virtual void alphaRender();  // slot 3
    void calcSamplingPos();

    // the sampling-position texture's size (128.0f)
    static float FLOW_TEX_SIZE;

    CloudUniform m_flowUniform;   // 0x20, CLOUD_UNIFORM_FLOW_0
    CloudUniform m_flowUniform2;  // 0x58, CLOUD_UNIFORM_FLOW_1
    unsigned char pad_90[0x8];    // CloudObjMan::createFlow allocates 0x98
};

}  // namespace cloud

#endif
