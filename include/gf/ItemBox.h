#ifndef GF_ITEMBOX_H
#define GF_ITEMBOX_H

#include "gf/GfItemInfo.h"

namespace gf {
// the item box: the entries of each item type (SDataGame 0xE98D8, 0x122EC bytes). The name is 1.0.0's: its
// GfItemBoxBase::setItemBox(ItemBox*, bool) clears 0x122EC bytes of it and its GfDataItem::getItemBox() returns
// SDataGame+0xE98D8. GfDataManager::fn_7100223650's offsets and the counts' bounds give each list's place and size;
// the member names are not the original's (by item type).
struct ItemBox {
    GfItemInfo m_type1[200];
    GfItemInfo m_type2[900];
    GfItemInfo m_type3[500];
    GfItemInfo m_type5[200];
    GfItemInfo m_type6[500];
    GfItemInfo m_type14[200];
    GfItemInfo m_type15[100];
    GfItemInfo m_type7[500];
    GfItemInfo m_type8[200];
    GfItemInfo m_type9[500];
    GfItemInfo m_type10[500];
    GfItemInfo m_type11[200];
    GfItemInfo m_type12[200];
    GfItemInfo m_type16[200];
    GfItemInfo m_type17[200];
    GfItemInfo m_type18[200];
    GfItemInfo m_type19[200];
    GfItemInfo m_type20[700];
    // one serial counter per ItemTypeInfo (GfItemBoxBase::fn_71002F3F98's set-up points each type's m_serial at
    // its own; the name is not the original's)
    unsigned int m_serials[19];
};
}  // namespace gf

#endif
