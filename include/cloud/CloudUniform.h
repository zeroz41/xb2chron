#ifndef CLOUD_CLOUDUNIFORM_H
#define CLOUD_CLOUDUNIFORM_H

#include "grlib/CGLibDblUniformBlock.h"

namespace cloud {

// the uniform block kinds; s_nUniformBlockSize holds each one's size. The enumerator names are not the original's:
// they name the create function that fills the block or the class whose constructor creates it.
enum CloudUniformType {
    CLOUD_UNIFORM_DEF,          // 0x150, CloudObjPlane fills it with createDefUniform
    CLOUD_UNIFORM_COLOR,        // 0x150, CloudObjPlane fills it with createColorUniform
    CLOUD_UNIFORM_CALC,         // 0x70, CloudCalcParams
    CLOUD_UNIFORM_3,            // 0x20
    CLOUD_UNIFORM_4,            // 0xE0
    CLOUD_UNIFORM_5,            // 0x20
    CLOUD_UNIFORM_FLOW_0,       // 0x3000
    CLOUD_UNIFORM_FLOW_1,       // 0x20
    CLOUD_UNIFORM_SKY_0,        // 0xD0
    CLOUD_UNIFORM_SKY_1,        // 0xA0
    CLOUD_UNIFORM_SKY_2,        // 0xF0
    CLOUD_UNIFORM_MDL_0,        // 0x60
    CLOUD_UNIFORM_MDL,          // 0xA0, bound as "U_MDL"
    CLOUD_UNIFORM_13,           // 0xE0
    CLOUD_UNIFORM_14,           // 0x20
    CLOUD_UNIFORM_15,           // 0xA0
    CLOUD_UNIFORM_16,           // 0x140
    CLOUD_UNIFORM_BLUR,         // 0x60, CloudObjPlane fills it with createBlurUniform
    CLOUD_UNIFORM_NUM
};

class CloudMdlParts;
class CMLObjData;

// a double-buffered uniform block of one CloudUniformType (0x38, no table)
class CloudUniform : public grlib::CGLibDblUniformBlock {
public:
    CloudUniform();
    ~CloudUniform();
    // num 0 creates one
    void createUniform(CloudUniformType type, unsigned int num);
    void updateData();
    void releaseUniform();

    static unsigned int s_nUniformBlockSize[CLOUD_UNIFORM_NUM];
};

}  // namespace cloud

#endif
