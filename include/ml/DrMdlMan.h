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
class DrMdoTextureMan;
class DrMdoSamplerMan;
class DrMdoTexSimpleMan;
class DrMdoSmlShadowMan;
class DrResOccUniformObj;
class DrResEtcUniformObj;
class DrMdoZSortMan;

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

    // one list of models, walked from m_pTop through DrMdlBase::m_pNext; updateList appends at m_pTail
    struct MdlList {
        DrMdlBase* m_pTop;
        DrMdlBase* m_pTail;
    };

    DrMan* m_pDrMan;  // 0x0, the constructor's argument
    DrMdoVertexMan* m_vertexMan;  // 0x8, the constructor's first DrMdoVertexMan
    // 0x10..0x50: the managers the constructor news (names not the original's)
    DrMdoTextureMan* m_textureMan;  // 0x10
    DrMdoSamplerMan* m_samplerMan;  // 0x18
    DrMdoMpfMan* m_mpfMan;  // 0x20, addMpfObj news it on first use (the name is not the original's)
    DrMdoTexSimpleMan* m_texSimpleMan;  // 0x28
    DrMdoSmlShadowMan* m_smlShadowMan;  // 0x30, updateList passes it to the moved models
    DrResOccUniformObj* m_occUniform;  // 0x38
    DrResEtcUniformObj* m_etcUniform;  // 0x40
    DrGpuCheckRender* m_gpuCheckRender;  // 0x48, the constructor's DrGpuCheckRender
    DrMdoZSortMan* m_zsortMan;  // 0x50
    // 0x58..0xA4: zeroed one by one by the constructor (separate scalars); their use is not recovered
    void* pad_58;
    void* pad_60;
    void* pad_68;
    // 0x70: a flag per render pass a model of this frame needs; DrMdoCtlPos::update sets entries 0-4 and 7-9 from
    // its m_stateFlags bits. m_pPassReq points at it (the name is not the original's)
    bool m_passReq[0x10];
    void* pad_80;
    void* pad_88;
    void* pad_90;
    void* pad_98;
    int pad_A0;
    // 0xA8: the model lists (the constructor clears them with one memset; updateList indexes them by view)
    MdlList m_lists[23];
    DrMdoZSortMan* m_curZSortMan;  // 0x218, the constructor sets it to m_zsortMan (the name is not the original's)
    // 0x220: the constructor points it at the list array at 0xA8; the shadow passes walk its first list
    MdlList* m_pMdlList;
    MdlList* m_pGrpList;  // 0x228, points at m_lists[10] (the name is not the original's)
    bool* m_pPassReq;  // 0x230, points at m_passReq (the name is not the original's)
    int pad_238;  // zeroed by the constructor
    // 0x23C: a bit per view (DrMdlBase::m_groups indexes it); the shadow passes render only models whose bit is set.
    // The constructor sets it to all ones.
    unsigned int m_shadowViewMask;
    int pad_240;  // zeroed by the constructor
    unsigned char pad_244[0x4];
};
}  // namespace ml

#endif
