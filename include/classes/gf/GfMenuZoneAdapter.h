#ifndef CLASSES_GF_GFMENUZONEADAPTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5E1F8; a zone (GfDataBdat 0x1AC's names): its name, development level, mercenary missions
class GfMenuZoneAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceNumberConverter;
    class ReferenceZoneConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuZoneAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuZoneAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_zoneId(0), m_teamId(0) {}
    virtual ~GfMenuZoneAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuZoneAdapter* create(unsigned int handle, unsigned int type, unsigned short zoneId, bool changed);
    bool update_ZoneName();
    bool update_ZoneLv();
    bool update_ZoneIcon();
    bool update_ZoneLvIcon();
    bool update_ZoneStatColor();
    bool update_ZoneNoticeDisp();
    bool update_ZoneNotice();
    static GfMenuZoneAdapter* createFromReferenceZone(unsigned int handle, unsigned int type, bool changed);
    static GfMenuZoneAdapter* createFromReference(unsigned int handle, unsigned int type,
                                                  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                  bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuZoneAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                        bool changed);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the zone from it; owned
    unsigned short m_zoneId;  // 0 shows nothing
    // a mercenary team: update_ZoneStatColor colours by what it does in the zone (nothing in this unit sets it; the
    // name is not the original's)
    unsigned int m_teamId;
};
}  // namespace gf

#endif
