#ifndef GF_GFMENUENHANCEADAPTER_H
#define GF_GFMENUENHANCEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui {
class UIObjectPlugin;
class UIStr;
}

namespace gf {

// the menus' enhancement texts (application/BF2/gf/menu/adapter/gf_menu_enhance_adapter.cpp). 1.0.0's adapter
// (table 0x7101190A78 in 1.0.0) shows an enhancement's caption; 3.0.1's linker dropped all of it but
// getEnhanceCaption as unused (no table in 3.0.1). The members below are 1.0.0's (names from its symbols).
class GfMenuEnhanceAdapter : public ::gf::GfMenuAdapter {
public:
    // where update takes the enhancement from (owned; 1.0.0 has item, item list, reference item and arts kinds)
    class IConverter {
    public:
        virtual ~IConverter() {}  // slot 0 (1.0.0 emits it as a weak function: inline)
        virtual unsigned int getEnhanceID() = 0;  // slot 2
    };
    // an art's enhancement at a level (table 0x7101190B38 in 1.0.0; the field names are not the original's)
    class ArtsConverter : public IConverter {
    public:
        ArtsConverter(unsigned int arts, unsigned int level) : m_arts(arts), m_level(level) {}
        virtual unsigned int getEnhanceID();  // slot 2
        unsigned int m_arts;
        unsigned int m_level;
    };
    // a display callback and the plugin create makes for it (1.0.0's s_typeSetups, one entry: a text plugin)
    struct TypeSetup {
        bool (GfMenuEnhanceAdapter::*func)(unsigned int);
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuEnhanceAdapter(ui::UIObjectPlugin* plugin, bool changed);
    virtual ~GfMenuEnhanceAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuEnhanceAdapter* create(unsigned int handle, unsigned int type, unsigned int enhance, bool changed);
    bool update_Caption(unsigned int enhance);
    // an adapter that takes its enhancement from the converter (owned) on each update
    static GfMenuEnhanceAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                    bool changed);
    static GfMenuEnhanceAdapter* createFromArts(unsigned int handle, unsigned int type, unsigned int arts,
                                                unsigned int level, bool changed);
    // the enhancement's caption (its Caption2 when menu layer 3 is usable and the table has a non-zero one), with
    // the enhancement's id as the text's owner; false when the enhancement or the text is not valid
    static bool getEnhanceCaption(unsigned int enhance, ui::UIStr& text);

    // the field names are not the original's: the callback create picks, where update takes the enhancement from
    // (owned) and the enhancement it shows (0: none)
    mm::mtl::Delegate<bool(unsigned int)> m_update;
    IConverter* m_converter;
    unsigned int m_enhance;
    unsigned int pad_5C;  // unknown: 1.0.0's constructor zeroes it (one 64-bit store with m_enhance), nothing reads it
};

}  // namespace gf

#endif
