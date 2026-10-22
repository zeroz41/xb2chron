#ifndef CLASSES_GF_GFMENUSHOPADAPTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5D920; a shop (GfDataBdat 0xED): its name, category, icons, owner
class GfMenuShopAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceConverter;
    class ReferenceNumberConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuShopAdapter::*func)(unsigned int shopId);
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuShopAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_shopId(0), pad_5C() {}
    virtual ~GfMenuShopAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuShopAdapter* create(unsigned int handle, unsigned int type, unsigned int shopId, bool changed);
    bool update_Name(unsigned int shopId);
    bool update_CategoryName(unsigned int shopId);
    bool update_Icon(unsigned int shopId);
    bool update_CategoryIcon(unsigned int shopId);
    bool update_Owner(unsigned int shopId);
    static GfMenuShopAdapter* createFromReference(unsigned int handle, unsigned int type, bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuShopAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                        bool changed);
    static GfMenuShopAdapter* createFromReference(unsigned int handle, unsigned int type,
                                                  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                  bool changed);
    mm::mtl::Delegate<bool(unsigned int)> m_update;  // its type's update_*, given the id; update shows what it returns
    IConverter* m_converter;  // update takes the id from it; owned
    unsigned int m_shopId;    // 0 shows nothing
    unsigned char pad_5C[4];
};
}  // namespace gf

#endif
