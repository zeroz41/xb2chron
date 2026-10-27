#ifndef CLASSES_GMK_LVLB_H
#define CLASSES_GMK_LVLB_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace gmk {

// the gimmick resource's header (magic 'LVLB', version 3), as TGmkList::createGmk reads it; its sections follow
// at +0x20 (the names are not the original's)
class LvlbHeader {
public:
    unsigned int m_magic;
    unsigned int m_size;  // the whole resource's: the sections end there
    unsigned int m_version;
    unsigned char pad_c[0x4];
    unsigned int m_flags;  // bit 0: the INFO names hold pointers (the STRG offsets were added once)
    unsigned char pad_14[0xc];
};

// one section of it: STRG, XFRM, INFO or the gimmick kind's; its data follows at +0x20 (the names are not the
// original's)
class LvlbSection {
public:
    unsigned int m_magic;
    unsigned int m_size;  // up to the next section
    unsigned int m_version;
    unsigned int m_count;
    unsigned int m_stride;  // the gimmick section's: one gimmick's data
    unsigned int m_infoIndex;  // the gimmick section's: its first gimmick's INFO entry
    unsigned int m_flags;  // the gimmick section's: bit 0, its gimmicks have no INFO entry (nor Xform)
    unsigned char pad_1c[0x4];
};

// an INFO entry (16 bytes): the gimmick's name, its Xform, its shape (AGmkBase::getMatrix switches on it); the
// names are not the original's
// an INFO entry (16 bytes) of a gimmick resource: the gimmick's name, its Xform, its shape (AGmkBase::getMatrix
// switches on it); AGmkBase::m_info points at one. TGmkList::initGmkBdatInfo finds the BDAT row whose "name" is
// m_name. The names are not the original's.
class LvlbInfo {
public:
    const char* m_name;
    unsigned int m_xformIndex;
    unsigned int m_shape;
};
// an XFRM entry (0x40 bytes): position, euler rotation and scale (toMatrix reads them so)
class Xform {
public:
    mm::Mat44& toMatrix(mm::Mat44& mat, bool noScale) const;

    mm::Vec3 m_pos;
    mm::Vec3 m_rot;
    mm::Vec3 m_scale;
    unsigned char pad_30[0x10];
};

}  // namespace gmk

#endif
