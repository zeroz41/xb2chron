#ifndef CLASSES_GMK_GMKBGMCONDINFO_H
#define CLASSES_GMK_GMKBGMCONDINFO_H

#include "mm/mtl/IntrusiveList.h"

namespace gmk {
class AGmkBase;
// an area BGM gimmick's condition: while its condition holds it is linked into GmkBgmCondInfoManager's list, whose
// first element names the field's gimmick BGM (GmkAreaBgm holds four at 0xe0). No table: a plain class.
class GmkBgmCondInfo : public mm::mtl::IntrusiveListNodeBase {
public:
    ~GmkBgmCondInfo();
    // 1.0.0 has it out of line (0xbc bytes, the destructor's body); 3.0.1 inlines it
    void dispose();
    bool isCondMatched() const;  // 1.0.0: GfGameCond::isGameCond(m_condition)
    // the gimmick it belongs to: its row (m_createInfo.m_bdatInfo, a GmkAreaBgm::BdatInfo) names the BGM (the name is
    // not the original's)
    const AGmkBase* m_owner;
    unsigned short m_condition;  // 0x18: 1.0.0's isCondMatched tests it (the name is not the original's)
    unsigned char pad_1a[0x6];
};
}  // namespace gmk

#endif
