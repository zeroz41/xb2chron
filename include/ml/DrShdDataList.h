#ifndef ML_DRSHDDATALIST_H
#define ML_DRSHDDATALIST_H

#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxVertex.h"
#include "ml/DrResFetch.h"

namespace ml {
class DrShdDataObj;

// The renderer's shared shaders and its built-in geometry (vertex and index buffers). The layout covers the
// buffers the bind/render functions use; the rest is not recovered yet. Field names are inferred from those
// functions' names; they are not the original's.
class DrShdDataList {
public:
    void createShader();
    void reloadShader(int);
    void bindShdVertex();
    void bindQuadsTex();
    void bindTriangle();
    void bindTriangleTex();
    void bindShdBoxVertex();
    void bindShdRainDropVertex();
    void bindShdEffVtx();
    void bindShdDepthCheck();
    void renderQuads();
    void renderTriangle();
    void renderBox();
    void renderRainDrop();
    void renderEffVtx(int instances);
    void renderPoint(int count);
    void renderPoint(int count, int instances);
    DrShdDataObj* getDebugShdObj(int i);
    DrShdDataObj* getSelectShdObj(int i);
    DrShdDataObj* getShadowShdObj(int i);
    DrShdDataObj* getPostShdObj(int i);
    DrShdDataObj* getComputeObj(int i);
    DrResFetch* getFetchShader(int i);

    unsigned char pad_0[0x18];
    // shader arrays the get*ShdObj getters index (the names are not the original's)
    DrShdDataObj* m_pDebugShdObj;  // 0x18
    DrShdDataObj* m_pSelectShdObj;  // 0x20
    DrShdDataObj* m_pShadowShdObj;  // 0x28
    DrShdDataObj* m_pPostShdObj;  // 0x30
    unsigned char pad_38[0x28];
    DrShdDataObj* m_pComputeObj;  // 0x60
    DrResFetch m_fetchShader[0x5B];  // 0x68: createWork sets each one's default vertex parameters
    unsigned char pad_618[0x20];
    grlib::CGLibVtxVertex m_shdVertex; // 0x638
    grlib::CGLibVtxVertex m_quadsTex; // 0x660
    grlib::CGLibVtxVertex m_triangle; // 0x688
    grlib::CGLibVtxVertex m_triangleTex; // 0x6B0
    grlib::CGLibVtxVertex m_shdBoxVertex; // 0x6D8
    unsigned char pad_700[0x78];
    grlib::CGLibVtxVertex m_shdRainDropVertex; // 0x778
    grlib::CGLibVtxVertex m_shdEffVtx; // 0x7A0
    grlib::CGLibVtxVertex m_shdDepthCheck; // 0x7C8
    unsigned char pad_7F0[0x28];
    grlib::CGLibVtxIndex m_quadsIndex; // 0x818
    grlib::CGLibVtxIndex m_triangleIndex; // 0x840
    grlib::CGLibVtxIndex m_boxIndex; // 0x868
    unsigned char pad_890[0x78];
    grlib::CGLibVtxIndex m_rainDropIndex; // 0x908
    grlib::CGLibVtxIndex m_effVtxIndex; // 0x930
};
}  // namespace ml

#endif
