#ifndef CLASSES_GF_GFGMKLOCATOR_H
#define CLASSES_GF_GFGMKLOCATOR_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "mm/mtl/Vector.h"

namespace gf {
// a gimmick the map menus show (GfMenuMapInfo::postUpdate, GfMenuObjWorldMap::setupIconTable ask getBindedGmk):
// held directly (m_gmk) or through an accessor (m_acc, when m_isAcc). 0x50 bytes: the stride of
// Vector<GfGmkLocator>::push_back, which copies the first 0x10 bytes and then the GmkAcc (copy constructor at 0x10).
// The field names are not the original's.
class GfGmkLocator {
public:
    // inline: Vector<GfGmkLocator>::destroy (gf_field_locator) runs dispose's stores, then GmkAcc's destructor, per
    // element
    ~GfGmkLocator() { dispose(); }
    const gmk::AGmkBase* getBindedGmk() const;
    void dispose();
    // whether the gimmick is a shop the menus mark: an NPC (GmkType 3 or 4) whose row has a "ShopID" whose
    // "ShopIcon" (BDAT 0xED) is neither 0x1A3 nor 0x1A4
    static bool isShop(const gmk::AGmkBase& gmk);

    const gmk::AGmkBase* m_gmk;
    bool m_isAcc;
    gmk::GmkAcc m_acc;
};
// a list of GfGmkLocator: GfGmkLocatorAtlas keeps a Vector of them at 0x440 (Vector<GfGmkLocators>::push_back copies
// the Vector, then the int at 0x28; 0x30 bytes). The field names are not the original's.
class GfGmkLocators {
public:
    mm::mtl::Vector<GfGmkLocator> m_locators;
    int pad_28;
};
}  // namespace gf

#endif
