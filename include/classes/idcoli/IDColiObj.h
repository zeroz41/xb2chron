#ifndef CLASSES_IDCOLI_IDCOLIOBJ_H
#define CLASSES_IDCOLI_IDCOLIOBJ_H

namespace idcoli {
// table 0x7100B7F088
// the base of every collision object: IDColiManager keeps them in ColiLinkLists linked through m_prev/m_next and
// IDColiParmsBase reads and sets their bits. The field names are not the original's.
class IDColiObj {
public:
    IDColiObj();
    virtual ~IDColiObj() {}  // slot 0
    virtual void release();  // slot 2
    virtual void sizeUpdate() {}  // slot 3
    virtual void update() {}  // slot 4
    virtual bool SweepAndPruneUpdate() { return false; }  // slot 5
    virtual void consistentUpdate() {}  // slot 6
    void setDeleteCall();

    IDColiObj* m_prev;  // 0x8
    IDColiObj* m_next;  // 0x10
    unsigned int m_state;  // 0x18, 1 << ColiState bits (IDColiParmsBase::isState/setState)
    // 0x1C, request bits: setDeleteCall's 1 and IDColiParmsBase::setMatrix's 8 shifted by IDColiManager::s_nStkIdx;
    // the shape creators set 0x20 (and 0x400 for their alternative shape)
    unsigned int m_flags;
    unsigned int m_attr;  // 0x20, 1 << ColiAtrr bits (IDColiParmsBase::isAttr)
    unsigned char pad_24[4];
    unsigned int pad_28;  // the constructor zeroes it; no reader seen yet
    unsigned int m_materialBit;  // 0x2C, IDColiParmsBase::setMaterialBit
    void* pad_30;  // the constructor zeroes it; no reader seen yet
    void* pad_38;  // the constructor zeroes it; no reader seen yet
    unsigned int pad_40;  // the constructor zeroes it; no reader seen yet
    unsigned char pad_44[4];
    void* m_userData;  // 0x48, IDColiParmsBase::setUserData (release clears it)
};
}  // namespace idcoli

#endif
