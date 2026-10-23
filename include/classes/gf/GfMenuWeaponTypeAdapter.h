#ifndef CLASSES_GF_GFMENUWEAPONTYPEADAPTER_H
#define CLASSES_GF_GFMENUWEAPONTYPEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5DDB8; a driver's weapon type (its name, icon, weapon points) and one of the arts the driver can use
// with it (its name, icons, texts, numbers, level, description)
class GfMenuWeaponTypeAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceDriverConverter;
    // an art and the driver's level of it (1.0.0's getDriverArts(DriverArts&) names the struct; the field names are
    // not the original's)
    struct DriverArts {
        unsigned int m_arts;
        unsigned int m_level;
    };
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuWeaponTypeAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuWeaponTypeAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_driverId(0), m_wpnType(0), m_artsIndex(0),
          m_param(0) {}
    virtual ~GfMenuWeaponTypeAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuWeaponTypeAdapter* create(unsigned int handle, unsigned int type, unsigned int driverId,
                                           unsigned int wpnType, unsigned int artsIndex, bool changed);
    bool update_WpnTypeName();
    bool update_WpnTypeIcon();
    bool update_WpnTypeWP();
    bool update_ArtsName();
    bool update_ArtsIconType();     // 1.0.0's name; the symbols call it fn_710034BDCC
    bool update_ArtsIconEnhance();  // 1.0.0's name; the symbols call it fn_710034BE6C
    bool update_ArtsIconReact();    // 1.0.0's name; the symbols call it fn_710034BF0C
    bool update_ArtsIconRange();    // 1.0.0's name; the symbols call it fn_710034BFAC
    bool update_ArtsTextType();
    bool update_ArtsTextReact();
    bool update_ArtsTextRange();
    bool update_ArtsNumDamage();    // 1.0.0's name; the symbols call it fn_710034C2B0
    bool update_ArtsNumRecast();    // 1.0.0's name; the symbols call it fn_710034C330
    bool update_ArtsLevel();        // 1.0.0's name; the symbols call it fn_710034C3B0
    bool update_ArtsIconLevel();    // 1.0.0's name; the symbols call it fn_710034C418
    bool update_ArtsDescription();
    bool update_ArtsWp();
    bool update_ArtsDriverLevel();
    bool update_ArtsLevel0Disp();
    bool update_ArtsLevelMaxDisp();
    bool update_ArtsEnhanceDescription();
    bool update_ArtsReleseLv();
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuWeaponTypeAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                              IConverter* converter, bool changed);
    static GfMenuWeaponTypeAdapter* createFromReferenceDriverWpnType(
        unsigned int handle, unsigned int type, unsigned short driver,
        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType, unsigned short artsIndex, bool changed);
    // the art of m_artsIndex the driver can use with the weapon type, and the driver's level of it; false when there
    // is none (inline: 1.0.0 has it out of line, 3.0.1 none)
    inline bool getDriverArts(DriverArts& arts);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the driver, weapon type and arts index from it; owned
    unsigned int m_driverId;  // 0 shows nothing
    unsigned int m_wpnType;
    unsigned int m_artsIndex;  // which of the arts GfMenuObjUtil::getEnableArts lists
    // update_ArtsLevel0Disp and update_ArtsLevelMaxDisp invert what they show when it is set, update_ArtsReleseLv
    // shows the level cap of this level (nothing in this unit sets it; the name is not the original's)
    unsigned int m_param;
};
}  // namespace gf

#endif
