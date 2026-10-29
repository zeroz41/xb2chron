#ifndef CLASSES_ML_DRMDOGRPOBJ_H
#define CLASSES_ML_DRMDOGRPOBJ_H

#include "classes/ml/DrMdlBase.h"
#include "classes/ml/DrResMdoSortGrp.h"

namespace ml { class DrPixlShadowCacheObj; }
namespace ml { class DrMdlObj; }

namespace ml {
// table 0x7100B7AC78
class DrMdoGrpObj : public ::ml::DrMdlBase {
public:
    DrMdoGrpObj(int viewNum, unsigned int listNum);
    virtual ~DrMdoGrpObj();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit() {}  // slot 5
    virtual void shadowRender();  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheOnlyRender();  // slot 9
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
    // a model of the group from a model resource and its name (fw::EffectManager::createMdl hands on its resource,
    // name and last argument; the parameter names are not the original's)
    DrMdlObj* createInstantMdl(const void* res, const char* name, unsigned int option);
    void updateList();
    void callNomSetupRender();
    void callZSortNomZpreePassRender();
    void callZSortThicknessRenderFirst();
    void callZSortThicknessRenderSecond();
    void callZSortNomRender();
    void callZSortGBuffRender();
    void callZSortLightPrePassRender();
    void callZSortNomAlphaRender();
    void callZSortNomSpAlphaRender();
    void callZSortNomRefractionRender();

    // the names below are not the original's
    // one list of objects (the constructor zeroes both words)
    struct MdlList {
        MdlList() : m_pTop(nullptr), m_pTail(nullptr) {}
        // deletes every model of the list and empties it (the destructor's loops)
        void deleteAll() {
            DrMdlBase* obj = m_pTop;
            while (obj != nullptr) {
                DrMdlBase* next = obj->m_pNext;
                delete obj;
                obj = next;
            }
            reset();
        }
        void reset() {
            m_pTop = nullptr;
            m_pTail = nullptr;
        }

        DrMdlBase* m_pTop;
        DrMdlBase* m_pTail;
    };
    MdlList* m_pLists;  // 0x28, m_listMax lists at the start of m_pListBuf
    MdlList** m_ppList;  // 0x30, the constructor points it after its MdlList entries in the same allocation
    MdlList m_lists[3];  // 0x38, emptied by the constructor, their models deleted by the destructor
    int m_listMax;  // 0x68, the constructor's list count clamped to 255
    int m_listNum;  // 0x6C, the count the render passes walk
    void* m_pListBuf;  // 0x70, allocated by the constructor (m_listMax * 0x18 bytes), freed by the destructor
    DrResMdoSortGrp m_sortGrp;  // 0x78
};
}  // namespace ml

#endif
