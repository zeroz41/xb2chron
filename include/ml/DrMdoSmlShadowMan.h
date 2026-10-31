#ifndef ML_DRMDOSMLSHADOWMAN_H
#define ML_DRMDOSMLSHADOWMAN_H

#include "ml/DrMdoResList.h"
#include "classes/ml/DrMan.h"
#include "mtl/MemManager.h"

namespace ml {

// A small shadow object of a model (DrMdlObj::m_pSmlShadowObj), kept in DrMdoSmlShadowMan's lists. Layout from 1.0.0's
// DrMdoSmlShadowObj(int, const unsigned char*, DrMan*) and ~DrMdoSmlShadowObj (3.0.1 inlines the destructor and has
// no copy of it). The field names are not the original's.
class DrMdoSmlShadowObj {
public:
    // data starts with the node count; the work holds 0x30 bytes per node, rounded up to 0x20
    DrMdoSmlShadowObj(int viewNum, const unsigned char* data, DrMan* drMan)
        : m_pPrev(nullptr), m_pNext(nullptr), m_pData(data), m_pBuff(nullptr), m_flags(0), m_viewNum(viewNum) {
        int size = *reinterpret_cast<const unsigned int*>(data) * 0x30;
        size += (0x20 - size % 0x20) % 0x20;
        m_pBuff = m_pCur = mtl::MemManager::allocate(drMan->m_allocHandle, size, 0x20, false, "no name", 0);
    }
    ~DrMdoSmlShadowObj() {
        if (m_pBuff != nullptr) {
            mtl::MemManager::deallocate(m_pBuff, 0, false);
            m_pBuff = nullptr;
        }
    }

    DrMdoSmlShadowObj* m_pPrev;    // 0x0
    DrMdoSmlShadowObj* m_pNext;    // 0x8
    const unsigned char* m_pData;  // 0x10: the constructor's data (its first int sizes m_pBuff)
    void* m_pBuff;                 // 0x18: allocated by the constructor
    void* m_pCur;                  // 0x20: m_pBuff at construction
    // 0x28: bit 0 = checkDisp's display bit; bit 14 + DrMan::s_nDblStockIdx = released (1.0.0 releaseObj),
    // updateList moves those to m_delList
    unsigned short m_flags;
    short m_viewNum;  // 0x2A: the view list the object is in (the constructor's int)
};

// sizeof 0x80 (DrMdlMan's constructor allocates that). The field names are not the original's.
class DrMdoSmlShadowMan {
public:
    DrMdoSmlShadowMan(DrMan* man);
    ~DrMdoSmlShadowMan();
    DrMdoSmlShadowObj* createObj(int viewNum, const unsigned char* data);
    void addObjList(int viewNum);
    void updateList();
    bool checkDisp();
    void delObjList();
    void changeViewNum(DrMdoSmlShadowObj* obj, int viewNum);

    int pad_0;                                       // 0x0: zeroed by the constructor
    int m_viewIdx;                                   // 0x4: the view list checkDisp/updateList walk
    DrMan* m_pDrMan;                                 // 0x8
    DrMdoResList<DrMdoSmlShadowObj> m_viewList[4];   // 0x10
    DrMdoResList<DrMdoSmlShadowObj> m_dblList[2];    // 0x50: per DrMan::s_nDblIdx, the new objects addObjList sorts
    DrMdoResList<DrMdoSmlShadowObj> m_delList;       // 0x70: released objects, deleted by delObjList
};
}  // namespace ml

#endif
