#ifndef ML_DRMDOZSORTMAN_H
#define ML_DRMDOZSORTMAN_H

#include "classes/ml/DrMdoZSortObj.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml {
class DrMan;
class DrMdoZSortObj;

// Sorts the view's depth-sorted objects into 512 buckets (a list per bucket, a bit per used bucket) and calls
// each object's render passes in bucket order. No class table (the constructor stores none). Field names are
// not the original's.
class DrMdoZSortMan {
public:
    enum { SORT_MAX = 512 };
    // setViewCloud's bucket (1.0.0's setViewLast uses 505)
    enum { SORT_CLOUD = 510 };

    DrMdoZSortMan(DrMan* drMan);
    ~DrMdoZSortMan();

    void beginViewWorld();
    void endViewWorld();
    void setViewCloud(DrMdoZSortObj* obj);
    void setViewWorldPos(DrMdoZSortObj* obj, const mm::Vec3& pos);
    void setViewWorldPosLastAlpha(DrMdoZSortObj* obj, const mm::Vec3& pos);
    void setViewWorldPosFastAlpha(DrMdoZSortObj* obj, const mm::Vec3& pos);

    void viewSetupRender();
    void viewZPrepassRender();
    void viewThicknessRenderFirst();
    void viewThicknessRenderSecond();
    void viewRender();
    void viewGBuffRender();
    void viewLightPrePassRender();
    void viewAlphaRender();
    void viewSpAlphaRender();
    void viewRefractionRender();

    // 1.0.0 has stockObj(DrMdoZSortObj*, int) out of line; 3.0.1 inlines it into setViewCloud
    void stockObj(DrMdoZSortObj* obj, int idx) {
        if (!(m_useBits[idx >> 5] & (1 << (idx & 0x1F)))) {
            m_useBits[idx >> 5] |= 1 << (idx & 0x1F);
            obj->setParent(nullptr);
            m_top[idx] = obj;
        } else {
            obj->setParent(m_last[idx]);
            m_last[idx]->setNext(obj);
        }
        obj->setNext(nullptr);
        m_last[idx] = obj;
    }

    DrMan* m_pDrMan;            // 0x0
    DrMdoZSortObj** m_top;      // 0x8, first object of each bucket (SORT_MAX)
    DrMdoZSortObj** m_last;     // 0x10, last object of each bucket (SORT_MAX)
    unsigned int* m_useBits;    // 0x18, one bit per bucket in use
    void* m_pBuff;              // 0x20, holds m_top, m_last and m_useBits
    DrMdoZSortObj* m_head;      // 0x28, endViewWorld chains the buckets from here
    DrMdoZSortObj* m_tail;      // 0x30
    // 0x38, called first by viewSetupRender and the depth/alpha passes, last by viewRender and viewGBuffRender
    DrMdoZSortObj* m_pSpecial;
    mm::Vec3NA m_viewPos;       // 0x40, DrCalcViewWork::m_viewPos at beginViewWorld
    unsigned char pad_4C[0x4];
    float m_sortFar;            // 0x50, 300.0f from the constructor
    float m_sortRate;           // 0x54, 0.8f from the constructor
};
}  // namespace ml

#endif
