#ifndef CLASSES_GF_GFMENUZONEMAPADAPTER_H
#define CLASSES_GF_GFMENUZONEMAPADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuZoneMapList; }

namespace gf {
// table 0x7100B5E350; a map of a zone or a point on it: its name
class GfMenuZoneMapAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuZoneMapAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 3.0.1 has none (1.0.0 neither)
    GfMenuZoneMapAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed),
          m_converter(nullptr),
          m_mapId(0),
          m_param(0),
          pad_60(0),
          m_groupMode(false) {}
    virtual ~GfMenuZoneMapAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuZoneMapAdapter* create(unsigned int handle, unsigned int type, unsigned int mapId,
                                        unsigned int param, bool changed);
    bool update_ZoneMapName();
    bool update_ZonePointName();
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuZoneMapAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                           IConverter* converter, bool changed);
    static GfMenuZoneMapAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuZoneMapList* list,
                                                unsigned int index, bool onPage, bool changed);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the map from it; owned
    unsigned int m_mapId;  // 0 shows nothing (the name is not the original's: IConverter::getMapId's)
    unsigned int m_param;  // update_ZonePointName's name row (the name is not the original's: IConverter::getParam's)
    unsigned int pad_60;  // the constructor zeroes it; nothing in 1.0.0 or 3.0.1's unit reads it
    // update_ZoneMapName's table: the groups' (the name is not the original's: IConverter::isGroupMode's)
    bool m_groupMode;
};
}  // namespace gf

#endif
