#ifndef CLASSES_GF_GFMENUADAPTER_H
#define CLASSES_GF_GFMENUADAPTER_H

#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/RTTI.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuRewriteNumber; }
namespace ui { class UIObjectPlugin; }
namespace ui { struct uiDateTime; }
namespace ui { class UIStr; }
namespace gf { struct ElapseTime; }
namespace mm { class Vec3; }
namespace mm { template <typename T> class Pnt; }

namespace gf {
// table 0x7100B59C80; GfMenuAdapterManager keeps its adapters in intrusive lists through the node base
class GfMenuAdapter : public ::mm::mtl::IntrusiveListNodeBase {
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
    void setUpdateAfter();  // GfMenuAdapterManager::setAfterUpdate of this adapter
    // the display plugin's modes (setDispSuspendMode passes its argument on too)
    void setDispAlphaMode(bool on);
    void setDispReverseMode(bool on);
    void setDispFadeMode(float time);
    void setDispSuspendMode(bool on);
    void setNumberReverseMode(bool on);  // the number plugin's m_reverse
    // the position plugin's screen adjustment: on, the area kept on screen and its margins
    void setPosAdjustScreen(bool on);
    void setPosAdjustSize(unsigned int width, unsigned int height);
    void setPosAdjustSizeOffs(short width, short height);
    int getNumberMax() const;  // the number plugin's
    // a rewrite: while it is enabled, setNumber shows its number instead (referenced)
    void setRewriteNumber(GfMenuRewriteNumber* rewrite);
    static ui::UIObjectPlugin* createPlugin(unsigned int handle, const PluginSetup& setup);
    static int compare(GfMenuAdapter* lhs, GfMenuAdapter* rhs);  // their numbers or texts: 0 same, 1 less, 2 more
    int getNumber() const;
    void setNumber(int number);
    void setNumberMin(int min);  // the number plugin's
    void setNumberMax(int max);  // the number plugin's
    void setNumberInterpolateMode(float interpolate);  // the number plugin's setInterpolate, when it is one
    void setChange();  // sets m_flags bit 0
    void setTime(const ui::uiDateTime& time);  // a time plugin's
    void setElapseTime(const ElapseTime& time);  // a time plugin's
    void setDisp(bool disp);
    void setText(const ui::UIStr& text);  // a text plugin's
    void setMulColor(const char* color);
    void setAddColor(const char* color);  // a colour plugin's
    void setColorMode(unsigned int mode);  // a colour plugin's
    void setColor(const char* color);  // a colour plugin's
    void setTextFacePattern(const char* pattern);  // a pattern plugin's (GfMenuElementComboAdapter: "element%02d")
    // a position plugin's: the screen position, the target an offset plugin moves to, the world position
    void setPos(const mm::Pnt<short>& pos);
    void setOffsetTargetPos(const mm::Pnt<short>& pos);
    void setPosWorld(const mm::Vec3& pos);
    bool isPosScreenAdjust() const;
    void setOffsetLimit(unsigned short x, unsigned short y);  // an offset plugin's
    void setPosOffsMode(unsigned int mode);  // a position plugin's
    // the plugin as a T when it is one, none otherwise (inline; the name is not the original's)
    template <typename T>
    T* getPlugin() const {
        return m_plugin != nullptr ? mm::mtl::rttiCast<T>(m_plugin) : nullptr;
    }
    ui::UIObjectPlugin* m_plugin;  // the constructor's, referenced
    unsigned int m_flags;          // bit 0: setChange sets it, update clears it; the constructor sets 1 or 3
    // an object setDisp shows or hides along with the plugin (0: none; the name is not the original's)
    unsigned int m_rowHandle;
    GfMenuRewriteNumber* m_rewriteNumber;  // setRewriteNumber's, referenced; the destructor releases it
};
}  // namespace gf

#endif
