#ifndef CLASSES_ML_DRGPUCHECKOBJ_H
#define CLASSES_ML_DRGPUCHECKOBJ_H

#include "grlib/CGLibOcclusionQuery.h"
#include "mm/Vec4.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7D6C8
class DrGpuCheckObj {
public:
    // DrMdlMan::createEffGpuCheckObj passes true for effects' objects (the parameter names are not the original's)
    DrGpuCheckObj(int type, bool eff);
    virtual ~DrGpuCheckObj();  // slot 0
    virtual void release();  // slot 2
    virtual bool isRender() const;  // slot 3
    virtual void setPause(bool);  // slot 4
    virtual void setPos(mm::Vec3 const&, float);  // slot 5
    virtual void setWorldPos(mm::Vec3 const&, float);  // slot 6
    virtual unsigned int isDeleteCall() const;  // slot 7: the release() bit of DrMan::s_nDblIdx
    virtual void update();  // slot 8
    virtual void render();  // slot 9

    // m_flags bits (the names are not the original's)
    enum {
        FLAG_POS = 1 << 0,            // setPos, shifted by DrMan::s_nDblStockIdx: m_pos[idx] is new
        FLAG_QUERIED = 1 << 2,        // render, shifted by DrMan::s_nDblIdx: a query was issued
        FLAG_RENDER = 1 << 4,         // isRender
        FLAG_QUERY = 1 << 5,          // update put the object in the instance ring: render queries it
        FLAG_CREATE = 1 << 6,         // the constructor's bool
        FLAG_PAUSE = 1 << 7,          // setPause
        FLAG_RELEASE = 1 << 8,        // release(), shifted by DrMan::s_nDblStockIdx
    };

    // the field names below are not the original's
    DrGpuCheckObj* m_prev;               // 0x8, DrMdlMan's list of the type
    DrGpuCheckObj* m_next;               // 0x10
    int m_type;                          // 0x18
    grlib::CGLibOcclusionQuery m_query;  // 0x20
    unsigned int m_instansOfs;           // 0x38, DrGpuCheckRender::m_instansOfs when update put it in the ring
    unsigned int m_flags;                // 0x3C
    mm::Vec4 m_pos[2];                   // 0x40, setPos (position, radius) by DrMan::s_nDblStockIdx
    mm::Vec4 m_worldPos;                 // 0x60, setWorldPos / update's copy of m_pos
    short m_holdCnt;                     // 0x70, frames the object stays visible
    short m_waitCnt;                     // 0x72
};
}  // namespace ml

#endif
