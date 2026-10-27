#ifndef CLASSES_GMK_LVLB_H
#define CLASSES_GMK_LVLB_H

namespace gmk {
// an INFO entry (16 bytes) of a gimmick resource: the gimmick's name, its Xform, its shape (AGmkBase::getMatrix
// switches on it); AGmkBase::m_info points at one. TGmkList::initGmkBdatInfo finds the BDAT row whose "name" is
// m_name. The names are not the original's.
class LvlbInfo {
public:
    const char* m_name;
    unsigned int m_xformIndex;
    unsigned int m_shape;
};
}  // namespace gmk

#endif
