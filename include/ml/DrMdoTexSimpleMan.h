#ifndef ML_DRMDOTEXSIMPLEMAN_H
#define ML_DRMDOTEXSIMPLEMAN_H

#include "ml/DrMdoResList.h"
#include "ml/DrResMdoTexSimple.h"

namespace ml {
class DrMan;

// The simple texture manager (no table: its constructor stores none): four lists of DrResMdoTexSimple. Field
// names are not the original's; the destructor empties them in the order 0x8, 0x18, 0x38, 0x28. update moves
// the m_list3 entries whose m_flags has bit 2 + s_nDblIdx set to m_list2.
class DrMdoTexSimpleMan {
public:
    DrMdoTexSimpleMan(DrMan* drMan);
    ~DrMdoTexSimpleMan();
    void update();  // DrMdlMan::setupEnd calls it

    DrMan* m_pDrMan;                           // 0x0
    // 0x8: by DrMan::s_nDblIdx; update creates their textures and moves them to m_list3
    DrMdoResList<DrResMdoTexSimple> m_list[2];
    DrMdoResList<DrResMdoTexSimple> m_list3;   // 0x28
    DrMdoResList<DrResMdoTexSimple> m_list2;   // 0x38
};
}  // namespace ml

#endif
