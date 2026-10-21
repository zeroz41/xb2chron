#ifndef CLASSES_GF_GFMENUDIFFADAPTER_H
#define CLASSES_GF_GFMENUDIFFADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5BA28; shows how two adapters compare (GfMenuAdapter::compare)
class GfMenuDiffAdapter : public ::gf::GfMenuAdapter {
public:
    // per type create is given: what the comparison updates, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuDiffAdapter::*func)(int result);
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuDiffAdapter(ui::UIObjectPlugin* plugin, bool changed) : GfMenuAdapter(plugin, false, changed) {}
    virtual ~GfMenuDiffAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuDiffAdapter* create(unsigned int handle, GfMenuAdapter* lhs, GfMenuAdapter* rhs, unsigned int type,
                                     bool changed);
    bool update_Icon(int result);
    bool update_MulCol(int result);
    bool update_Sub(int result);
    bool update_DispSameOn(int result);
    bool update_DispSameOff(int result);
    mm::mtl::Delegate<bool(int)> m_update;  // its type's update_*, given compare's result; update shows what it returns
    GfMenuAdapter* m_lhs;
    GfMenuAdapter* m_rhs;
};
}  // namespace gf

#endif
