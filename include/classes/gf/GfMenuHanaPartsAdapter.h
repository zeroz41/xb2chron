#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B5C948; a part of Hana (GfDataBdat 0x17C): its name, icon, and the ether it needs
class GfMenuHanaPartsAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    class ReferenceNumberConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuHanaPartsAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // a blade and one of its parts, copied as one: update_needEther passes it by value (the original's one 8-byte
    // reload of both after its switch on the part); the type and its name are not the original's
    struct HanaParts {
        // the blade whose circuits update_needEther asks GfGameUtilHana about (nothing in this unit sets it; the name
        // is not the original's)
        unsigned int m_hanaId;
        unsigned int m_partsId;  // GfDataBdat 0x17C's row; 0 shows nothing
    };
    // inline: 1.0.0 has it out of line (it leaves the part unset), 3.0.1 none
    GfMenuHanaPartsAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr) {
        m_parts.m_hanaId = 0;
    }
    virtual ~GfMenuHanaPartsAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuHanaPartsAdapter* create(unsigned int handle, unsigned int type, unsigned int partsId, bool changed);
    bool update_partsText();
    bool update_partsIcon();
    bool update_needEther();
    static GfMenuHanaPartsAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list, int index,
                                                  bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuHanaPartsAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                             IConverter* converter, bool changed);
    static GfMenuHanaPartsAdapter* createFromReference(unsigned int handle, unsigned int type,
                                                       mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                       bool changed);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the part from it; owned
    HanaParts m_parts;
};
}  // namespace gf

#endif
