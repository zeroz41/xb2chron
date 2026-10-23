#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
class GfMenuIDList;

// table 0x7100B5E0D8; a world map (GfDataBdat 0x5D's rows): its name, its zone's development, whether it is the
// current map
class GfMenuWorldMapAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    class ReferenceConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuWorldMapAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuWorldMapAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_mapId(0), pad_5C() {}
    virtual ~GfMenuWorldMapAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuWorldMapAdapter* create(unsigned int handle, unsigned int type, unsigned short mapId, bool changed);
    bool update_WorldMapName();
    bool update_DevelopPoint();
    bool update_DevelopLvIcon();
    bool update_CurrentDisp();
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuWorldMapAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                            IConverter* converter, bool changed);
    static GfMenuWorldMapAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list,
                                                 int index, bool onPage, bool changed);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it fills this unit
    // between createFromList and createFromReference and returns create's adapter. What it does: createFromList
    // with GfMenuMissionAdapter::MissionListConverter (table 0x7100B5E1A8) in place of ListConverter: the map is
    // the second id (MenuID::m_subId) of the GfMenuIDList entry at the index (-1: the selected one; onPage: an
    // index of the page shown), which it references. No caller in 3.0.1 (nothing references it).
    static GfMenuWorldMapAdapter* fn_710034D118(unsigned int handle, unsigned int type, GfMenuIDList* list,
                                                int index, bool onPage, bool changed);
    static GfMenuWorldMapAdapter* createFromReference(unsigned int handle, unsigned int type, bool changed);
    // the zone a map belongs to, 0 for a map with none; inline: 1.0.0 has it out of line, 3.0.1 none
    inline unsigned int convMap2Zone(unsigned int mapId);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the map from it; owned
    unsigned short m_mapId;   // 0 shows nothing
    unsigned char pad_5A[2];
    unsigned char pad_5C[4];
};
}  // namespace gf

#endif
