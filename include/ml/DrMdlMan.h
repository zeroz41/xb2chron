#ifndef ML_DRMDLMAN_H
#define ML_DRMDLMAN_H

#include "classes/ml/DrMdlBase.h"
#include "ml/DrResMdoSeamMemMan.h"

namespace ml {
class DrMan;
class DrMdoVertexMan;
class DrMdoMpfMan;
class DrGpuCheckBase;
class DrGpuCheckRender;
class DrMdlObj;
class DrMdoGrpObj;
class DrStmReadCheck;
class DrGpuCheckObj;
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
    ~DrMdlMan();
    void addDelList(int view);
    void updateList(int view);
    void setupEnd();
    void apply();
    void deleteAll();
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
        // unlinks obj (inline: the name is not the original's)
        void remove(DrMdlBase* obj) {
            DrMdlBase* prev = obj->m_pPrev;
            DrMdlBase* next = obj->m_pNext;
            if (prev == nullptr) {
                if (next == nullptr) {
                    m_pTop = nullptr;
                    m_pTail = nullptr;
                } else {
                    m_pTop = next;
                    next->m_pPrev = nullptr;
                }
            } else if (next == nullptr) {
                m_pTail = prev;
                prev->m_pNext = nullptr;
            } else {
                prev->m_pNext = next;
                obj->m_pNext->m_pPrev = obj->m_pPrev;
            }
            obj->m_pPrev = nullptr;
            obj->m_pNext = nullptr;
        }
        // deletes every model (virtual destructor) and empties the list (inline: the name is not the original's)
        void deleteAll() {
            DrMdlBase* obj = m_pTop;
            while (obj != nullptr) {
                DrMdlBase* next = obj->m_pNext;
                delete obj;
                obj = next;
            }
            m_pTop = nullptr;
            m_pTail = nullptr;
        }
        // links obj at the end (inline: the name is not the original's)
        void pushBack(DrMdlBase* obj) {
            if (m_pTail == nullptr) {
                m_pTop = obj;
                m_pTail = obj;
                obj->m_pPrev = nullptr;
            } else {
                m_pTail->m_pNext = obj;
                obj->m_pPrev = m_pTail;
                m_pTail = obj;
            }
            obj->m_pNext = nullptr;
        }
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
    // 0x50: one per view; the constructor news the first, the destructor deletes all four
    DrMdoZSortMan* m_zsortMan[4];
    // 0x70: a flag per render pass a model of this frame needs; DrMdoCtlPos::update sets entries 0-4 and 7-9 from
    // its m_stateFlags bits. m_pPassReq points at it (the name is not the original's)
    // by view: begin, apply and applyView point m_pPassReq at the view's 13 flags
    bool m_passReq[4][13];
    unsigned char pad_A4[0x4];
    // 0xA8: the lists (the constructor clears them with one memset). The names are not the original's.
    MdlList m_mdlLists[4];  // 0xA8: by view (addDelList moves the view's new models here)
    MdlList m_mdlAddLists[2];  // 0xE8: createMdl adds by DrMan::s_nDblStockIdx; setupEnd empties by s_nDblIdx
    MdlList m_mdlDelLists[4];  // 0x108: by view, the models updateList found deleted; addDelList deletes them
    DrResChankList<DrGpuCheckObj> m_gpuCheckLists[4];  // 0x148: by type
    DrResChankList<DrGpuCheckObj> m_gpuCheckAddLists[2];  // 0x188: by DrMan::s_nDblStockIdx (createGpuCheckObj)
    DrResChankList<DrGpuCheckObj> m_gpuCheckDelLists[4];  // 0x1A8: by type, deleted by addDelList
    DrResChankList<DrStmReadCheck> m_stmLoadList;  // 0x1E8: setupEnd updates them and deletes the finished ones
    DrResChankList<DrStmReadCheck> m_stmLoadAddLists[2];  // 0x1F8: by DrMan::s_nDblStockIdx (createStmLoadObj)
    DrMdoZSortMan* m_curZSortMan;  // 0x218, the constructor sets it to m_zsortMan (the name is not the original's)
    // 0x220: the constructor points it at m_mdlLists[0]; the shadow passes walk it
    MdlList* m_pMdlList;
    // 0x228, points at m_gpuCheckLists[0]; apply updates its objects (the name is not the original's)
    DrResChankList<DrGpuCheckObj>* m_pGpuCheckList;
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
