#ifndef CLASSES_GF_GFGMKLOCATOR_H
#define CLASSES_GF_GFGMKLOCATOR_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"

namespace gf {
// a gimmick the map menus show (GfMenuMapInfo::postUpdate, GfMenuObjWorldMap::setupIconTable ask getBindedGmk):
// held directly (m_gmk) or through an accessor (m_acc, when m_isAcc). 0x50 bytes: the stride of
// Vector<GfGmkLocator>::push_back, which copies the first 0x10 bytes and then the GmkAcc (copy constructor at 0x10).
// The field names are not the original's.
class GfGmkLocator {
public:
    const gmk::AGmkBase* getBindedGmk() const;
    void dispose();

    const gmk::AGmkBase* m_gmk;
    bool m_isAcc;
    gmk::GmkAcc m_acc;
};
}  // namespace gf

#endif
