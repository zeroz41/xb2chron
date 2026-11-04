#ifndef CLASSES_GF_GFMENUDRIVERLIST_H
#define CLASSES_GF_GFMENUDRIVERLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a driver list's element (4 bytes: setupFromParty adds the drivers' BDAT ids); the field name is not the original's
class MenuDriverInfo {
public:
    unsigned int m_driver;
};

// table 0x7100B5F280
class GfMenuDriverList : public ::ui::UIListInfo< ::gf::MenuDriverInfo> {
public:
    GfMenuDriverList() {}  // the symbols name no copy (inline in create)
    virtual ~GfMenuDriverList();  // slot 0
    static GfMenuDriverList* create();

    // setupFromParty's parameter (1.0.0's symbol names the type; its field names are not the original's)
    class PartySetup {
    public:
        ::ui::UIListInfoBase::SetupParam m_param;  // handed to setup
        // 0: the party's three drivers (GfGameParty::getDriverBdatId 0-2); 1 and 2: GfPartySelect::getDriverList's
        // list of that type
        int m_type;
        bool m_selectFlag;  // getDriverList's third argument
        // 3.0.1: with GfMenuObjUtil::isValidExpansion(3), the drivers go through GfDataDriver::getIraFront
        bool m_convertDriver;
        bool m_skipUnused;  // with m_convertDriver, a type 1/2 list drops drivers GfDataDriver::isActivateUnuse holds for
    };
    // fills the list with the drivers m_type picks (none: the list stays as it was)
    void setupFromParty(const PartySetup& setup);

    // setupFromIraDriver's parameter (2.0.0's symbols name the type; the field names are not the original's)
    class IraDriverSetup {
    public:
        ::ui::UIListInfoBase::SetupParam m_param;  // handed to setup
        int m_index;  // GfDataParty::getDriver's index for parties 0-2; -1 leaves the list as it was
    };
    // 2.0.0's symbols name it. What it does: unless m_index is -1, sets the list up and adds
    // GfDataParty::getDriver(m_index, party) for parties 0, 1 and 2 when it is not 0 and GfDataDriver::isActivateUnuse
    // does not hold for it (GfMenuObjCharSelectIra::updateDriverList).
    void setupFromIraDriver(const IraDriverSetup& setup);
};
}  // namespace gf

#endif
