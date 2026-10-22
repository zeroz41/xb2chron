#ifndef CLASSES_GF_GFMENUEVTHERTERADAPTER_H
#define CLASSES_GF_GFMENUEVTHERTERADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B5BC28; an event theater entry (GfDataBdat 0xFD, 0xFE with add-on menu layer 3): its title and
// thumbnail (the class name spells "Therter")
class GfMenuEvTherterAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuEvTherterAdapter::*func)(unsigned int theaterId);
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 3.0.1 has no copy of it
    GfMenuEvTherterAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_theaterId(0), m_converter(nullptr) {}
    virtual ~GfMenuEvTherterAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuEvTherterAdapter* create(unsigned int handle, unsigned int type, unsigned int theaterId,
                                          bool changed);
    static GfMenuEvTherterAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list,
                                                  int index, bool changed);
    // inline: 3.0.1 has no copy of it (the name is the other adapters' createFromCoverter)
    static inline GfMenuEvTherterAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                             IConverter* converter, bool changed);
    bool update_Title(unsigned int theaterId);
    bool update_Thumb(unsigned int theaterId);
    mm::mtl::Delegate<bool(unsigned int)> m_update;  // its type's update_*, given the id; update shows what it returns
    unsigned int m_theaterId;  // 0 shows nothing
    IConverter* m_converter;  // update takes the id from it; owned
};
}  // namespace gf

#endif
