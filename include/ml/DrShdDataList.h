#ifndef ML_DRSHDDATALIST_H
#define ML_DRSHDDATALIST_H

#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibUniformArray.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxStmOut.h"
#include "grlib/CGLibVtxVertex.h"
#include "ml/DrResFetch.h"

namespace grlib {
template <typename T0>
class CGLibShdListBase;
}

namespace ml {
class DrMan;
class FileResTh;
class DrResShdObjMot;
class DrShdDataObj;
class DrResShdMpf;
class DrResShdPrePass;
class DrResShdShw;
class DrResShdStreamOut;

// The renderer's shared shaders and its built-in geometry (vertex and index buffers). The layout covers the
// buffers the bind/render functions use; the rest is not recovered yet. Field names are inferred from those
// functions' names; they are not the original's.
class DrShdDataList {
public:
    DrShdDataList(DrMan* drMan);
    ~DrShdDataList();
    void createWork();
    void createShader();
    void releaseShader();
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
    DrResShdMpf* getMpfObj(int i);
    DrResShdPrePass* getPrePassObj(int i);
    DrResShdShw* getShwObj(int i);
    DrResShdStreamOut* getStmOutObj(int i);
    grlib::CGLibOneUniformBlock* getAlphaTestUniform(float alpha);
    void createSphere(DrMan* drMan);
    void createSpot(DrMan* drMan);
    void createCylinder(DrMan* drMan);
    void createRainDropGeometry(DrMan* drMan);
    void createAlphaTestBlock();

    FileResTh* m_pRes;  // 0x0: the shader package file (the name is not the original's)
    DrMan* m_pDrMan;  // 0x8
    void* m_pResShdWork;  // 0x10: createShader builds the DrResShd* set-ups in it (the name is not the original's)
    // the shader lists createShader fills from the package's extension entries: [0] debug, [1] select, [2] shadow,
    // [3] post, [4] stream out, [5] mpf, [6] pre-pass, [7] shadow casters, [8] object motion, [9] compute (the
    // name is not the original's)
    DrShdDataObj* m_pShdObj[10];  // 0x18
    DrResFetch m_fetchShader[0x5B];  // 0x68: createWork sets each one's default vertex parameters
    grlib::CGLibShdListBase<DrShdDataObj>* m_pShdList;  // 0x618 (the name is not the original's)
    // the shader set-ups the get*Obj getters index (the names are not the original's)
    DrResShdMpf* m_pMpfObj;  // 0x620
    DrResShdPrePass* m_pPrePassObj;  // 0x628
    DrResShdShw* m_pShwObj;  // 0x630
    // the built-in vertex buffers (the destructor releases them in a loop): [0] full-screen quad (bindShdVertex),
    // [1] textured quad (bindQuadsTex), [2] full-screen triangle (bindTriangle), [3] textured triangle
    // (bindTriangleTex), [4] box (bindShdBoxVertex), [5] sphere (createSphere), [6] cylinder (createCylinder),
    // [7] spot cone (createSpot), [8] rain drop (bindShdRainDropVertex), [9] effect vertices (bindShdEffVtx),
    // [10] depth check quad (bindShdDepthCheck), [11] a quad in the XZ plane (the name is not the original's)
    grlib::CGLibVtxVertex m_vertex[12];  // 0x638
    // their index buffers: [0] quads, [1] triangle, [2] box, [3] sphere, [4] cylinder, [5] spot, [6] rain drop,
    // [7] effect vertices (the name is not the original's)
    grlib::CGLibVtxIndex m_index[8];  // 0x818
    // the bone matrices this frame and last frame: DrMdoSetup::uniformBlock_Bone/OldBone bind them (names inferred)
    grlib::CGLibVtxStmOut m_boneStmOut; // 0x958
    grlib::CGLibVtxStmOut m_oldBoneStmOut; // 0x980
    // createAlphaTestBlock builds them: one per alpha test step of 0.1 (the name is not the original's)
    grlib::CGLibUniformArray<grlib::CGLibOneUniformBlock> m_alphaTestBlock;  // 0x9A8 (0x28 bytes: its m_mem is 0x9C0)
    DrResShdStreamOut* m_pStmOutObj;  // 0x9D0
    DrResShdObjMot* m_pObjMotObj;  // 0x9D8 (the name is not the original's)

};
}  // namespace ml

#endif
