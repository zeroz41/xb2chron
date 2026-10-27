#ifndef ML_DRPIXLPOSTOBJCUBEMAPIBL_H
#define ML_DRPIXLPOSTOBJCUBEMAPIBL_H

#include "ml/DrPixlPostObj.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibTextureBuffer; class CGLibDblUniformBlock; }
namespace ml { class DrPixlRenderCubeMapMipMap; }

namespace ml {
// DrPixlPostMan::m_cubeMapIBL: renders the global IBL's cube map into one of two 64x64 mip-mapped cube maps,
// blending it in over 30 frames when the camera moves (the field names are not the original's)
class DrPixlPostObjCubeMapIBL : public DrPixlPostObj {
public:
    DrPixlPostObjCubeMapIBL(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjCubeMapIBL();
    void render();
    grlib::CGLibTextureBuffer* getPremTexture() const;
    const mm::Mat44& getSHMatrix(unsigned int idx) const;
    void setUniformBlock(unsigned int location) const;

    bool m_reset;                                 // 0x18: set by the constructor, render then blends nothing in
    unsigned char pad_19[0x7];
    DrPixlRenderCubeMapMipMap* m_cubeMap[2];      // 0x20: the current one is m_cubeMap[m_bufIdx]
    int m_mipNum;                                 // 0x30: 5
    unsigned char pad_34[0xC];
    mm::Mat44 m_shMatrix[2][3];                   // 0x40: per buffer
    mm::Mat44 m_mtx;                              // 0x1C0: identity at first
    mm::Vec3 m_pos;                               // 0x200: the position of the last render
    int m_blendCount;                             // 0x210: frames left of the blend in
    unsigned int m_bufIdx;                        // 0x214
    grlib::CGLibDblUniformBlock* m_uniformBlock;  // 0x218
};
}  // namespace ml

#endif
