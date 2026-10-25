#ifndef CLASSES_ML_DRGPUCHECKOBJ_H
#define CLASSES_ML_DRGPUCHECKOBJ_H

#include "grlib/CGLibOcclusionQuery.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7D6C8
class DrGpuCheckObj {
public:
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
        FLAG_RENDER = 1 << 4,         // isRender
        FLAG_CREATE = 1 << 6,         // the constructor's bool
        FLAG_PAUSE = 1 << 7,          // setPause
        FLAG_RELEASE = 1 << 8,        // release(), shifted by DrMan::s_nDblStockIdx
    };

    unsigned char pad_8[0x18];
    grlib::CGLibOcclusionQuery m_query;  // 0x20 (the name is not the original's)
    unsigned char pad_38[0x4];
    unsigned int m_flags;                // 0x3C (the name is not the original's)
    unsigned char pad_40[0x34];
};
}  // namespace ml

#endif
