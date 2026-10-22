#ifndef CLASSES_GF_GFMENUBATTLEADAPTER_H
#define CLASSES_GF_GFMENUBATTLEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5A0A0; create constructs it as a GfMenuAdapter, then installs this table
class GfMenuBattleAdapter : public ::gf::GfMenuAdapter {
public:
    class ReferenceIndexConverter;
    virtual ~GfMenuBattleAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // a plugin of that type (an entry of its 0x20-byte table) on the handle, and an adapter for it (null without one)
    static GfMenuBattleAdapter* create(unsigned int handle, unsigned int type);
    // which one of its kind it shows: create clears it, callers set it (GfMenuObjSpecialGauge's gauge levels),
    // update_PartyGauge reads it (the name is not the original's)
    int m_index;
    unsigned char pad_34[0x2C];  // create's delegate of the table entry's getter, at 0x38
};
}  // namespace gf

#endif
