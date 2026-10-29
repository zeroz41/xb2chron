#ifndef CLASSES_EVENT_GROUP_H
#define CLASSES_EVENT_GROUP_H
#include "mm/mtl/FixedVector.h"

namespace event { class CharaObj; }

namespace event {
// table 0x7100B3CFF0
class Group {
public:
    // inline: its D2/D0 and table are weak copies after the unit's out-of-line code (GroupManager's D2 stores its
    // table and clears the list)
    virtual ~Group() {}  // slot 0
    // 1.0.0's Group::clear (0x71000E140C): the list's clear
    void clear() { m_charas.clear(); }

    // 1.0.0's Group::push/pop(const CharaObj*) add and remove (memmove) entries; the name is not the original's
    mm::mtl::FixedVector<const CharaObj*, 128> m_charas;  // 0x8 (count at 0x408)
    // 1.0.0's Group::Group zeroes them
    long pad_410;
    int pad_418;
    unsigned char pad_41c[0x4];
    long pad_420;
};
}  // namespace event

#endif
