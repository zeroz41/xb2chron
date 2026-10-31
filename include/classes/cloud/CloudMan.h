#ifndef CLASSES_CLOUD_CLOUDMAN_H
#define CLASSES_CLOUD_CLOUDMAN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/AllocHandle.h"

namespace ml {
class Scn;
class IDrDrawWorkInfo;
class DrMdoZSortMan;
class DrResMdoSortCloud;
}  // namespace ml
namespace mm { class Col3; }

namespace cloud {
class CloudDataMan;
class CloudVertexMan;
class CloudTextureMan;
class CloudShaderMan;
class CloudObjMan;

// table 0x7100B7A0F8. The cloud system's top: three allocators (top, data, work), its managers and the sort object
// the depth-sorted alpha pass draws it through. Field names are not the original's.
class CloudMan : public ::mm::mtl::PtrSingleton< ::cloud::CloudMan> {
public:
    CloudMan(ml::Scn* scn, mtl::ALLOC_HANDLE handle, unsigned int size);
    virtual ~CloudMan();  // slot 0

    void planeOn(bool on);
    void planeSideOn(bool on);
    void skyOn(bool on);
    void mdlOn(bool on);
    void setHeight(float height);
    float getHeight() const;
    bool isHole() const;
    void setCldNum(unsigned int num);
    unsigned int getCldNum() const;
    void beginSetup();
    void begin(float frame);
    void end();
    void apply(const ml::IDrDrawWorkInfo* info, ml::DrMdoZSortMan* zsort);
    void alphaRender(const ml::IDrDrawWorkInfo* info);
    void finalRender(const ml::IDrDrawWorkInfo* info);
    void tail();
    // forwards to CloudObjReduction's (the same registers, a plain branch: both static)
    static unsigned int getPixelMem(unsigned int& mem, unsigned int width, unsigned int height);
    const mm::Col3& getPlaneCol(unsigned int idx) const;

    // double-buffer indices: tail flips both, the constructor sets 0 and 1
    static int s_nDblDfIdx;
    static int s_nDblStIdx;

    mtl::ALLOC_HANDLE m_hTop;           // 0x8, "CloudTop": the constructor's size + 0x1000
    mtl::ALLOC_HANDLE m_hData;          // 0xC, "CloudData" in m_hTop (0x380000)
    mtl::ALLOC_HANDLE m_hWork;          // 0x10, "CloudWork" in m_hTop: every manager is allocated from it
    unsigned char pad_14[0x4];
    ml::Scn* m_pScn;                    // 0x18
    bool m_isSetupWait;                 // 0x20, true until beginSetup has the data (begin calls it while set)
    unsigned char pad_21[0x7];
    // 0x28, zeroed by the constructor: a bit array CloudMdlParts::isDisp reads (a set bit hides the part)
    unsigned int* m_pReserved;
    CloudDataMan* m_pDataMan;           // 0x30
    CloudVertexMan* m_pVertexMan;       // 0x38
    CloudTextureMan* m_pTextureMan;     // 0x40
    CloudShaderMan* m_pShaderMan;       // 0x48
    CloudObjMan* m_pObjMan;             // 0x50
    ml::DrResMdoSortCloud* m_pSortObj;  // 0x58, apply stocks it in DrMdoZSortMan's cloud bucket
    float m_frame;                      // 0x60, begin's argument (1.0f from the constructor)
    float m_rate;                       // 0x64, 1.0f from the constructor (its use is not known)
};
}  // namespace cloud

#endif
