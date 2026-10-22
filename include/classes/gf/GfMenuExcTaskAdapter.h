#ifndef CLASSES_GF_GFMENUEXCTASKADAPTER_H
#define CLASSES_GF_GFMENUEXCTASKADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B5BCB8; an exchange task (GfDataBdat 0xF2): its name
class GfMenuExcTaskAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuExcTaskAdapter::*func)(unsigned int taskId);
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuExcTaskAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_taskId(0), m_converter(nullptr) {}
    virtual ~GfMenuExcTaskAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuExcTaskAdapter* create(unsigned int handle, unsigned int type, unsigned int taskId, bool changed);
    static GfMenuExcTaskAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list, int index,
                                                bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuExcTaskAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                           IConverter* converter, bool changed);
    bool update_Name(unsigned int taskId);
    unsigned int m_taskId;  // 0 shows nothing
    mm::mtl::Delegate<bool(unsigned int)> m_update;  // its type's update_*, given the id; update shows what it returns
    IConverter* m_converter;  // update takes the id from it; owned
};
}  // namespace gf

#endif
