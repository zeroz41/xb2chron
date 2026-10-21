#ifndef CLASSES_GF_GFMENUADAPTER_H
#define CLASSES_GF_GFMENUADAPTER_H

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B59C80
class GfMenuAdapter {
public:
    // what createPlugin makes for a UI object
    struct PluginSetup {
        unsigned int m_type;  // 0 number, 1 image index, 2 text, 3 disp, 4 pos, 5 world pos, 6 offset, 7 time,
                              // 8 color, 9 pattern
        int m_min;            // a number plugin's setMin (7: the time plugin's second argument)
        int m_max;            // a number plugin's setMax
        unsigned char pad_C[4];
    };
    // it takes a reference to the plugin and adds itself to GfMenuAdapterManager (with the first flag)
    GfMenuAdapter(ui::UIObjectPlugin* plugin, bool managerFlag, bool changed);
    virtual ~GfMenuAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static ui::UIObjectPlugin* createPlugin(unsigned int handle, const PluginSetup& setup);
    static int compare(GfMenuAdapter* lhs, GfMenuAdapter* rhs);  // their numbers or texts: 0 same, 1 less, 2 more
    int getNumber() const;
    void setNumber(int number);
    void setDisp(bool disp);
    void setMulColor(const char* color);
    unsigned char pad_8[0x10];
    ui::UIObjectPlugin* m_plugin;  // the constructor's, referenced
    unsigned int m_flags;          // bit 0: setChange sets it, update clears it; the constructor sets 1 or 3
    unsigned char pad_24[0xC];
};
}  // namespace gf

#endif
