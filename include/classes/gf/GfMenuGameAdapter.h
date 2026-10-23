#ifndef CLASSES_GF_GFMENUGAMEADAPTER_H
#define CLASSES_GF_GFMENUGAMEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5BE10; the game's state: play time, money, field time, weather, map and location, time of day,
// mercenaries, the console's date and time, the chapter, and the menu's referenced number and item type
class GfMenuGameAdapter : public ::gf::GfMenuAdapter {
public:
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuGameAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuGameAdapter(ui::UIObjectPlugin* plugin, bool changed) : GfMenuAdapter(plugin, false, changed) {}
    virtual ~GfMenuGameAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // the adapter it makes for a UI object (by its handle), of a type (an index into its plugin setups)
    static GfMenuGameAdapter* create(unsigned int handle, unsigned int type, bool changed);
    bool update_GamePlayTime();
    bool update_Money();
    bool update_FieldTime();
    bool update_WeatherIcon();
    bool update_CloudIcon();
    bool update_MapName();
    bool update_LocationName();
    bool update_TimeZoneName();
    bool update_TimeZoneIcon();
    bool update_ReferenceNum();
    bool update_MercenariesName();
    bool update_MercenariesLv();
    bool update_MercenariesPoint();
    bool update_MercenariesPointMax();
    bool update_RealYear();
    bool update_RealTime();
    bool update_Chapter();
    bool update_DispAccess();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's type table ends at
    // update_DispAccess). A member because it is type 18 of this class's TypeSetup table. What it does: takes the
    // item type GfMenuReference::fn_710036934C returns; for a valid type (1 to 20) shows
    // GfMenuItemUtil::getIconNumber(type, 0, number, false)'s icon and returns true, otherwise false.
    bool fn_710033E76C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is type 19 of this
    // class's TypeSetup table. What it does: for a valid item type from GfMenuReference::fn_710036934C (1 to 20)
    // shows 0 when GfMenuItemUtil::canCountStack(type), otherwise GfItemBoxBase::fn_71002F9DD4(type) of the
    // GfItemBox singleton (the sum of the stack counts of that type's items), and returns true; false otherwise.
    bool fn_710033E7CC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is type 20 of this
    // class's TypeSetup table. What it does: for a valid item type from GfMenuReference::fn_710036934C (1 to 20)
    // shows GfItemBoxBase::fn_71002F9F6C(type) of the GfItemBox singleton (the number of that type's entries) and
    // returns true; false otherwise.
    bool fn_710033E840();
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    // the index update_ReferenceNum passes to GfMenuReference::getReferenceNumber (nothing in this unit sets it; the
    // name is not the original's)
    unsigned int m_referenceIndex;
    unsigned char pad_54[4];
};
}  // namespace gf

#endif
