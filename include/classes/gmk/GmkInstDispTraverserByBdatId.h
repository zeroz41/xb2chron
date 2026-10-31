#ifndef CLASSES_GMK_GMKINSTDISPTRAVERSERBYBDATID_H
#define CLASSES_GMK_GMKINSTDISPTRAVERSERBYBDATID_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6F080 (weak: onTraverse is inline, emitted after the unit's functions; setDispByGmkType and
// setDispByGmkTypeAndBdatId build one on the stack and pass it to GmkManager::traverseGmkInst)
class GmkInstDispTraverserByBdatId {
public:
    GmkInstDispTraverserByBdatId(int bdatId, bool disp) : m_bdatId(bdatId), m_disp(disp), pad_d(false), m_traversed(false) {}
    // shows or hides a valid gimmick of the row (any row for an id below 1)
    virtual void onTraverse(gmk::AGmkBase const& gmk) {  // slot 0
        if (!gmk.isValid()) {
            return;
        }
        if (m_bdatId >= 1 && m_bdatId != gmk.m_createInfo.m_bdatId) {
            return;
        }
        if (pad_d) {
            fn_71005D3C54(gmk, true, false);
        } else {
            fn_71005D3C54(gmk, false, m_disp);
        }
        m_traversed = true;
    }
    // GmkManager::traverseGmkInst calls its F with each gimmick (inline; the name is not the original's)
    void operator()(gmk::AGmkBase const& gmk) { onTraverse(gmk); }
    // the BDAT row whose gimmicks it shows or hides, below 1 for all of them (the name is not the original's)
    int m_bdatId;  // 0x8
    bool m_disp;   // 0xc: show or hide (the setters' bool; the name is not the original's)
    // 0xd: both setters clear it; when set, onTraverse passes true, false instead (meaning unknown)
    bool pad_d;
    bool m_traversed;  // 0xe: set by onTraverse once it handled a gimmick (the name is not the original's)
};
}  // namespace gmk

#endif
