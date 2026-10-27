#ifndef CLASSES_GMK_GMKMAPOBJ_H
#define CLASSES_GMK_GMKMAPOBJ_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkMapObjGob; }

namespace gmk {
// table 0x7100B6C2D8
class GmkMapObj : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        BdatInfo() {}  // user-provided: Vector<BdatInfo>::resize stores only the defaults (pads left)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned short m_condition = 0;  // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned char m_priority = 0;    // the row's "Priority" (when the sheet has that column)
        // squared distances from the row's Visible_XZ, Visible_Y, Invisible_XZ, Invisible_Y (an Invisible one
        // at most its Visible one becomes Visible + 1)
        float m_visibleXZSq = 0.0f;
        float m_visibleYSq = 0.0f;
        float m_invisibleXZSq = 0.0f;
        float m_invisibleYSq = 0.0f;
    };
    virtual ~GmkMapObj();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(6);
    unsigned char pad_48[0x14];  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
