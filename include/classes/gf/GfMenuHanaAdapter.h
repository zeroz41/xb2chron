#ifndef CLASSES_GF_GFMENUHANAADAPTER_H
#define CLASSES_GF_GFMENUHANAADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "gf/GfGameUtilHana.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5C778; Hana (a blade id) and one of her part slots: her ether, power, role, attribute, parts
class GfMenuHanaAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceIndexConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuHanaAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line (it leaves the blade unset), 3.0.1 none
    GfMenuHanaAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_partsId(0) {}
    virtual ~GfMenuHanaAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuHanaAdapter* create(unsigned int handle, unsigned int type, unsigned int hanaId, bool changed);
    bool update_ether();
    bool update_equipPower();
    bool update_maxPower();
    bool update_roleText();
    bool update_atrText();
    bool update_atrIcon();
    bool update_bustupIcon();
    bool update_equipIcon();
    bool update_rankPower();
    bool update_maxRankPower();
    bool update_partsExpandIcon();
    bool update_equipColor();
    static GfMenuHanaAdapter* createFromReferenceIndex(unsigned int handle, unsigned int type, unsigned int index,
                                                       bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuHanaAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                        bool changed);
    // whether a circuit part slot (9 to 14) is open (result: GfGameUtilHana's answer); false for other slots
    static bool isOpenCircuit(unsigned int hana, unsigned int partsId, RESULT_HANA& result);
    // the part Hana has in a slot (1 to 14), 0 for none
    static unsigned int getEquipParts(unsigned int hana, unsigned int partsId);
    static bool isEquipParts(unsigned int hana, unsigned int partsId, unsigned int item, RESULT_HANA& result);
    static bool isMakeParts(unsigned int partsId, unsigned int item, RESULT_HANA& result);
    static bool isCrystalParts(unsigned int partsId, unsigned int item, RESULT_HANA& result);
    static int getHanaCount();
    static unsigned int getSortTableId(unsigned int partsId);
    static unsigned int getMakeSortTableId(unsigned int partsId);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the blade from it; owned
    unsigned int m_partsId;  // a part slot (GfDataBdat 0x17C's row); nothing in this unit sets it
    unsigned int m_hanaId;  // the blade
};
}  // namespace gf

#endif
