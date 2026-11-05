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

    const ml::IDrDrawWorkInfo* m_pInfo;  // 0x0, apply's argument
    unsigned char pad_8[0x88];
    mm::Mat44 m_skyMat[2];       // 0x90, CloudObjSky::updateUniform sends [0], then [1] twice
    mm::Mat44 m_invMat;          // 0x110, apply inverts a matrix into it (CloudObjReduction::update sends it)
    mm::Vec3 m_skyPos;           // 0x150, CloudObjSky::updateUniform sends it with m_far * 0.9
    unsigned char pad_160[0x30];
    float m_skySpeed;            // 0x190, CloudObjSky::updateParams scales both scrolls by it
    float m_height;              // 0x194, CloudMan::setHeight/getHeight
    unsigned char pad_198[0x4];
    unsigned int m_cldNum;       // 0x19C, CloudMan::setCldNum (0 or 1)/getCldNum
    unsigned char pad_1A0[0x18];
    mm::Col3 m_planeCol[2];      // 0x1B8, CloudMan::getPlaneCol (0 picks the first)
    unsigned char pad_1D0[0x144];
    float m_skyWindAngle;        // 0x314, degrees: CloudObjSky::updateParams's scroll direction (cos, 1, sin)
    unsigned char pad_318[0x8];
    float m_detailDir[3];        // 0x320, CloudObjSky's detail scroll per unit of time
    float m_skyParam[3];         // 0x32C, CloudObjSky::updateUniform sends them reversed; [2] also moves the detail
    float m_skyRateH;            // 0x338, CloudObjSky's scroll rate along x and z
    float m_skyRateV;            // 0x33C, along y
    unsigned char pad_340[0x4];
    float m_skyScale;            // 0x344, squared into CloudObjSky's scroll
    unsigned char pad_348[0x10];
    int m_skyTexSize;            // 0x358, CloudObjSky's detail target is this square
    unsigned int m_skyShader;    // 0x35C, CloudObjSky::renderSkyPoli's shader variant
    unsigned char pad_360[0x6C];
    float m_near;                // 0x3CC (apply's; CloudObjReduction sends far - near, far * near, far: the names
    float m_far;                 // 0x3D0  are inferred from that use)
    unsigned char pad_3D4[0x4C];
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
