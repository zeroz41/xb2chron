#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_PARTYBLADECONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_PARTYBLADECONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter/IConverter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfMenuObjUtil.h"

namespace gf {
// table 0x7100B5C728
class GfMenuGfObjAdapter::PartyBladeConverter : public ::gf::GfMenuGfObjAdapter::IConverter {
public:
    PartyBladeConverter(unsigned char driver, int blade, bool flag) : m_driver(driver), m_blade(blade), m_flag(flag) {}
    // the blade in that slot of the party driver's (driver 0: in a chain attack, the acting party member's)
    virtual GF_OBJ_HANDLE* getGfObjHandle() {  // slot 0
        return GfMenuObjUtil::getBladeHandleFromPartySlot(getDriver(), m_blade, m_flag);
    }
    virtual PartyBladeConverter* fromPartyBlade() { return this; }  // slot 2
    unsigned int getDriver() const {  // inline (the name is not the original's)
        unsigned int driver = m_driver;
        if (driver == 0) {
            if (GfMenuManager::isBattleState(3)) {
                int id = GfMenuReference::getChainAttackActionPartyID();
                driver = id < 3 && id > -1 ? id : 0;
            } else {
                driver = 0;
            }
        }
        return driver;
    }
    // changePartyBlade sets the first two (the names are not the original's)
    unsigned int m_driver;
    int m_blade;
    bool m_flag;  // getBladeHandleFromPartySlot's flag
};
}  // namespace gf

#endif
