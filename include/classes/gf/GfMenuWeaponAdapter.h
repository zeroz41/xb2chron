#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5DC40; a weapon (GfDataWeapon): its name, stats, type, caption and image
class GfMenuWeaponAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceBladeConverter;
    class ReferenceChipConverter;
    // a blade (GfMenuReference's at an index) and the core chip a GfMenuReferenceNumber holds
    // (GfMenuObjBlWeapon2::setupWeapon fills one); the field names are not the original's
    struct ReferenceChip {
        unsigned int m_reference;
        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_chip;
    };
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuWeaponAdapter::*func)(unsigned int weaponId);
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuWeaponAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_weaponId(0), pad_5C() {}
    virtual ~GfMenuWeaponAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuWeaponAdapter* create(unsigned int handle, unsigned int type, unsigned int weaponId, bool changed);
    bool update_Name(unsigned int weaponId);
    bool update_Atk(unsigned int weaponId);
    bool update_Guard(unsigned int weaponId);
    bool update_Critical(unsigned int weaponId);
    bool update_Balance(unsigned int weaponId);
    bool update_TypeName(unsigned int weaponId);
    bool update_Caption(unsigned int weaponId);  // 1.0.0's name; the symbols call it fn_710034B4AC
    bool update_Image(unsigned int weaponId);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuWeaponAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                          IConverter* converter, bool changed);
    static GfMenuWeaponAdapter* createFromReferenceBlade(unsigned int handle, unsigned int type,
                                                         unsigned int reference, bool changed);
    static GfMenuWeaponAdapter* createFromReferenceChip(unsigned int handle, unsigned int type,
                                                        const ReferenceChip& chip, bool changed);
    mm::mtl::Delegate<bool(unsigned int)> m_update;  // its type's update_*, given the id; update shows what it returns
    IConverter* m_converter;  // update takes the weapon from it; owned
    unsigned int m_weaponId;  // 0 shows nothing
    unsigned char pad_5C[4];
};
}  // namespace gf

#endif
