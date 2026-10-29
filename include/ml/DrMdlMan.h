#ifndef ML_DRMDLMAN_H
#define ML_DRMDLMAN_H

namespace ml {
class DrMan;
class DrMdoVertexMan;
class DrMdoMpfMan;
class DrGpuCheckBase;
class DrGpuCheckRender;
class DrMdlObj;
class DrMdoGrpObj;
class DrStmReadCheck;
class DrMdlBase;
class DrPixlShadowObj;
class DrPixlShadowCacheObj;

// DrMan's model manager (DrMan::m_mdlMan). Only what this file's users read is recovered; the field names are
// not the original's.
class DrMdlMan {
public:
    DrMdlMan(DrMan* man);
    DrMdlObj* createMdl(const void* resource, const char* name, int arg);
    DrMdoGrpObj* createInstantGrp(int arg, unsigned int viewNum);
    DrGpuCheckBase* createGpuCheckObj(int type);
    DrStmReadCheck* createStmLoadObj(const char* name);
    // news a DrGpuCheckObj (bool true) and appends it to the type's list
    DrGpuCheckBase* createEffGpuCheckObj(int type);
    bool shadowRender(DrPixlShadowObj* shadowObj);
    bool shadowCacheRender(DrPixlShadowCacheObj& cacheObj);
    void shadowCacheAddRender(int);
    void callShadowCacheUpdate(unsigned long);
    void addMpfObj();
    void delMpfObj();

    // one list of models, walked from m_pTop through DrMdlBase::m_pNext
    struct MdlList {
        DrMdlBase* m_pTop;
        unsigned char pad_8[0x8];
    };

    DrMan* m_pDrMan;  // 0x0, the constructor's argument
    DrMdoVertexMan* m_vertexMan;  // 0x8, the constructor's first DrMdoVertexMan
    unsigned char pad_10[0x10];
    DrMdoMpfMan* m_mpfMan;  // 0x20, addMpfObj news it on first use (the name is not the original's)
    unsigned char pad_28[0x20];
    DrGpuCheckRender* m_gpuCheckRender;  // 0x48, the constructor's DrGpuCheckRender
    unsigned char pad_50[0x1D0];
    // 0x220: the constructor points it at the list array at 0xA8; the shadow passes walk its first list
    MdlList* m_pMdlList;
    unsigned char pad_228[0x14];
    // 0x23C: a bit per view (DrMdlBase::m_groups indexes it); the shadow passes render only models whose bit is set.
    // The constructor sets it to all ones.
    unsigned int m_shadowViewMask;
    unsigned char pad_240[0x8];
};
}  // namespace ml

#endif
