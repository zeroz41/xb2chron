#ifndef CLASSES_GF_GFMENUPOUCHADAPTER_H
#define CLASSES_GF_GFMENUPOUCHADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5D808; a driver's pouch slot: its remaining time
class GfMenuPouchAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceDriverConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuPouchAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuPouchAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), pad_58(), m_remainTime(0.0f), m_pouch(0) {}
    virtual ~GfMenuPouchAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuPouchAdapter* create(unsigned int handle, unsigned int type, unsigned short pouch,
                                      unsigned int driver, bool changed);
    static GfMenuPouchAdapter* createFromReferenceDriver(unsigned int handle, unsigned int type, unsigned int pouch,
                                                         unsigned int reference, bool changed);
    static GfMenuPouchAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                  bool changed);
    bool update_PouchRemainTime();
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*: update shows what it returns
    IConverter* m_converter;  // update takes the pouch and driver from it; owned
    unsigned char pad_58[4];
    float m_remainTime;  // the pouch's, as update last saw it
    unsigned int m_pouch;
    unsigned int m_driver;
};
}  // namespace gf

#endif
