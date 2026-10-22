#ifndef GF_MENUOFFSET_H
#define GF_MENUOFFSET_H

#include "mm/Vec3.h"

namespace gf {

// where a menu shows itself at an object: an offset from the object, or from one of its bones (DataParamAcc and the
// data objects' getMenuOffset give one); the field names are not the original's
struct MenuOffset {
    mm::Vec3 m_offset;
    const char* m_bone;  // none or empty: the object's own position
};

}  // namespace gf

#endif
