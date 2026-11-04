#ifndef CLASSES_GF_TUNK_B51E90_H
#define CLASSES_GF_TUNK_B51E90_H

#include "mm/Vec3.h"

namespace gf {
// table 0x7100B51E90 (no RTTI, no 1.0.0 symbol): new in 3.0.1, its functions are in gf_field_locator's unit. A
// locator GfMenuLocation keeps for its list 4 (an id, a position count and a position); the table holds only the
// destructor, so every virtual is inline and the constructing unit emits it.
class GfFieldNpcLocator {
public:
    // what the constructor is given (2.0.0's symbols name it): GfMenuLocation::postUpdate passes its requested id
    struct CreateInfoByRSC {
        unsigned short m_id;
    };

    // Placeholder (fn_7100270094): zeroes the fields, then takes info's id when info is given
    GfFieldNpcLocator(const CreateInfoByRSC* info);
    virtual ~GfFieldNpcLocator() {  // slot 0
        dispose();
    }
    // 2.0.0's symbols name it. What it does: zeroes m_id, m_posNum, pad_20 and sets m_pos to mm::Vec3::zero.
    void dispose();
    // 2.0.0's symbols name it. What it does: finds the gimmick set of the current map (GfFieldGimmick's
    // getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList, gmk::GmkManager::findGmkSet) and the NPC m_id names
    // (GmkNpcManager::getNpcIdInfoByNpcId), and reads its world position (GfObjAcc::getWorldTransformNoSync).
    void update();

    unsigned short m_id;     // 0x8: the constructor's info id (the name is not the original's)
    unsigned char m_posNum;  // 0xA: GfMenuLocation's list-4 data count (the name is not the original's)
    mm::Vec3 m_pos;          // 0x10: GfMenuLocation::getLocatorData's list-4 position (the name is not the original's)
    unsigned short pad_20;   // 0x20: the constructor and dispose zero it
};
}  // namespace gf

#endif
