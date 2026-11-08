#ifndef CLOUD_CLOUDCALCPARAMS_H
#define CLOUD_CLOUDCALCPARAMS_H

#include "mm/Col3.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "cloud/CloudUniform.h"

namespace grlib { class CGLibRenderTarget; class CGLibDepthBuffer; class CGLibDepthTarget; }
namespace ml { class IDrDrawWorkInfo; }

namespace cloud {
// the cloud parameters CloudObjMan allocates (0x4F0); only what CloudMan reads is named, and the names are not the
// original's
class CloudCalcParams {
public:
    CloudCalcParams();
    // CloudObjMan::update's first call each frame (stores the draw info)
    void apply(const ml::IDrDrawWorkInfo* info);

    const ml::IDrDrawWorkInfo* m_pInfo;  // 0x0, apply's argument
    unsigned char pad_8[0x48];
    mm::Mat44 m_flowMat;         // 0x50, CloudObjFlow::update sends it first
    mm::Mat44 m_skyMat[2];       // 0x90, CloudObjSky::updateUniform sends [0], then [1] twice
    mm::Mat44 m_invMat;          // 0x110, apply inverts a matrix into it (CloudObjReduction::update sends it)
    mm::Vec3 m_skyPos;           // 0x150, CloudObjSky::updateUniform sends it with m_far * 0.9
    unsigned char pad_160[0x10];
    float m_flowBlend;           // 0x170, CloudObjFlow::update sends it and 1 - it
    unsigned char pad_174[0xC];
    float m_uvScale0;            // 0x180, CloudObjFlow and the sky uniform send it (with m_uvScale1)
    unsigned char pad_184[0x4];
    float m_uvScale1;            // 0x188
    unsigned char pad_18C[0x4];
    float m_skySpeed;            // 0x190, CloudObjSky::updateParams scales both scrolls by it
    float m_height;              // 0x194, CloudMan::setHeight/getHeight
    float m_flowParam;           // 0x198, CloudObjFlow::update sends it twice
    unsigned int m_cldNum;       // 0x19C, CloudMan::setCldNum (0 or 1)/getCldNum
    unsigned char pad_1A0[0x18];
    mm::Col3 m_planeCol[2];      // 0x1B8, CloudMan::getPlaneCol (0 picks the first)
    unsigned char pad_1D0[0x12C];
    float m_skyCol0[3];          // 0x2FC, the sky uniform sends both with alpha 1
    float m_skyCol1[3];          // 0x308
    float m_skyWindAngle;        // 0x314, degrees: CloudObjSky::updateParams's scroll direction (cos, 1, sin)
    // the sky uniform sends sqrt((radius + height)^2 - radius^2): a horizon distance (names inferred from that)
    float m_skyRadius;           // 0x318
    float m_skyAtmHeight;        // 0x31C
    float m_detailDir[3];        // 0x320, CloudObjSky's detail scroll per unit of time
    float m_skyParam[3];         // 0x32C, CloudObjSky::updateUniform sends them reversed; [2] also moves the detail
    float m_skyRateH;            // 0x338, CloudObjSky's scroll rate along x and z
    float m_skyRateV;            // 0x33C, along y
    float m_skyFactor;           // 0x340, the sky uniform sends it times 10 (with m_skyScale)
    float m_skyScale;            // 0x344, squared into CloudObjSky's scroll
    float m_skyParam2[2];        // 0x348, sent by the sky uniform after the scaled pair
    unsigned char pad_350[0x8];
    int m_skyTexSize;            // 0x358, CloudObjSky's detail target is this square
    unsigned int m_skyShader;    // 0x35C, CloudObjSky::renderSkyPoli's shader variant
    float m_mdlCol0[3];          // 0x360, CloudObjMdl::updateUniform sends both with alpha 1
    float m_mdlCol1[3];          // 0x36C
    float m_mdlRateH;            // 0x378, CloudObjMdl::update's scroll rate along x and z (times m_skySpeed)
    float m_mdlRateV;            // 0x37C, along y
    float m_heightRange;         // 0x380, CloudObjMan::update sends its inverse after m_height
    float m_heightParam;         // 0x384, sent after it
    unsigned char pad_388[0x44];
    float m_near;                // 0x3CC (apply's; CloudObjReduction sends far - near, far * near, far: the names
    float m_far;                 // 0x3D0  are inferred from that use)
    unsigned char pad_3D4[0xC];
    float m_mdlVec[3];           // 0x3E0, CloudObjMdl::updateUniform sends it with w 0
    float m_lightVec0[3];        // 0x3EC, the model and sky uniforms send both (with w 0 / 1)
    unsigned char pad_3F8[0x8];
    float m_lightVec1[3];        // 0x400
    unsigned char pad_40C[0x14];
    grlib::CGLibRenderTarget* m_pTarget;  // 0x420, CloudObjMan renders only while it is set
    grlib::CGLibDepthTarget* m_pDepthTarget0;  // 0x428, CloudObjReduction's counter/stencil renders draw to it
    grlib::CGLibDepthTarget* m_pDepthTarget1;  // 0x430, CloudObjReduction reads its sub texture
    grlib::CGLibDepthBuffer* m_pDepth;    // 0x438, CloudObjMan::alphaRender sets it with m_pTarget
    unsigned char pad_440[0x20];
    CloudUniform m_uniform;               // 0x460, CLOUD_UNIFORM_CALC
    // CloudObjReduction::alphaFastRender sets the GPU's tiled cache from m_tiledCache[m_tiledIdx] (names not the
    // original's)
    struct TiledCache {
        unsigned int m_width;   // 0x0
        unsigned int m_height;  // 0x4
        bool m_isEnable;        // 0x8
        unsigned char pad_9[0x1B];
    };
    unsigned short m_tiledIdx;          // 0x498
    unsigned char pad_49a[0x2];
    TiledCache m_tiledCache[2];         // 0x49C
    unsigned char pad_4e4[0xC];
};
}  // namespace cloud

#endif
