#ifndef CLASSES_GF_GFUNPOPBLADEIDS_H
#define CLASSES_GF_GFUNPOPBLADEIDS_H

#include "mm/mtl/FixedVector.h"
#include "classes/gmk/GmkBlade.h"

namespace gmk { class AGmkBase; }

namespace gf {
// table 0x7100B51A58 (weak: onTraverse is inline, emitted after gf_field_gimmick's functions; the constructor is
// gf_field_gimmick's). 0x360 bytes.
class GfUnpopBladeIds {
public:
    // the reserve blades (GfDataBlade::getListReserver) that are in the village (GfGameUtil::isBladeInVillage),
    // less those a blade gimmick (GmkType 0x2F) already shows
    GfUnpopBladeIds();
    // drops the id of a blade gimmick from the list
    virtual void onTraverse(gmk::AGmkBase const& gmk) {  // slot 0
        const gmk::GmkBlade& blade = static_cast<const gmk::GmkBlade&>(gmk);
        if (blade.m_bladeId == 0) {
            return;
        }
        unsigned short id = blade.m_bladeId;
        unsigned long i = 0;
        for (; i != m_ids.size(); ++i) {
            if (m_ids.begin()[i] == id) {
                break;
            }
        }
        if (i != m_ids.size()) {
            m_ids.erase(m_ids.begin() + i);
        }
    }
    // GmkManager::traverseGmkInst calls its F with each gimmick (inline; the name is not the original's)
    void operator()(gmk::AGmkBase const& gmk) { onTraverse(gmk); }

    mm::mtl::FixedVector<unsigned short, 422> m_ids;  // 0x8: the blade ids (the name is not the original's)
};
}  // namespace gf

#endif
