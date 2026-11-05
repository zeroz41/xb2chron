#ifndef CLASSES_GF_GFMENUFULLSCREEN_H
#define CLASSES_GF_GFMENUFULLSCREEN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIInputSwitcher.h"
#include "gf/GfMenuTypes.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuFullScreen; }
namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5E850
class GfMenuFullScreen : public ::mm::mtl::PtrSingleton< ::gf::GfMenuFullScreen> {
public:
    // a layer group of the screen: its ui layer, the layers it showed before (reciveUIEvent's back event reopens the
    // last), the object registLayerObject names and whether setShadowLayer made it a shadow (the back event skips
    // those). The names are not the original's.
    struct Layer {
        unsigned short m_id;
        mm::mtl::FixedVector<unsigned int, 8> m_history;
        unsigned int m_object;
        bool m_shadow;
    };
    // registLayerParam's entry: a layer and what it is opened with (the names are not the original's)
    struct LayerParam {
        unsigned int m_layer;
        GfMenuTypes::Param m_param;
    };

    // 1.0.0's constructor (3.0.1 has no copy: build inlines it)
    explicit GfMenuFullScreen(const GfSetupParam& param)
        : m_initialized(false), m_screen(0), m_nextScreen(0), m_layers(), m_pushHistory(true), m_switching(false),
          m_fadeInTime(0), m_fadeOutTime(0), m_inputBorder(0), m_enableEvent(true), m_fadeOut(true), m_fadeIn(true),
          m_nextLayer(0), m_waitFrames(0), m_sub(), m_inputSwitcher(8) {}
    virtual ~GfMenuFullScreen();  // slot 0
    static void build(const GfSetupParam& param);
    // 1.0.0's: sets m_initialized (3.0.1 has no copy: build inlines it)
    void initialize(const GfSetupParam& param) {
        m_initialized = true;
    }
    static void destroy();
    // 1.0.0's: clears m_initialized (3.0.1 has no copy: destroy inlines it)
    void finalize() {
        m_initialized = false;
    }
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    static void reciveUIEvent(const ui::EventData& event, unsigned int arg);
    // 1.0.0's: a layer shown, or no switch running (3.0.1 has no copy: close inlines it)
    static bool isDisp() {
        GfMenuFullScreen* screen = get();
        if (screen == nullptr) {
            return false;
        }
        if (screen->m_layers[0].m_id != 0 || screen->m_layers[1].m_id != 0 || screen->m_layers[2].m_id != 0 ||
            screen->m_layers[3].m_id != 0) {
            return true;
        }
        return !screen->m_switchSeq.isValid();
    }
    // 1.0.0's: empties a layer group (3.0.1 has no copy)
    void resetLayer(unsigned short group) {
        m_layers[group].m_id = 0;
        m_layers[group].m_history.clear();
        m_layers[group].m_object = 0;
        m_layers[group].m_shadow = false;
    }
    // shows a screen (GfMenuManager::openMenu opens screen 2 so)
    static void open(unsigned int screen, bool fadeOut, bool fadeIn);
    static void close(bool fadeOut, bool fadeIn);
    static bool isOpen();       // a screen shown, or one being switched to
    static bool isSwitching();
    static unsigned int getScreenLayerID(unsigned int screen);  // 0 past the eighth
    // its UIInputSwitcher's, without a full screen false/0/nothing
    static bool setInputObject(unsigned int index, unsigned int handle);
    static unsigned int getInputObject(unsigned int index);
    static void enableInput(unsigned int index);
    static void disableInput();
    static void registLayerParam(unsigned int layer, const GfMenuTypes::Param& param);
    static bool getLayerParam(unsigned int layer, GfMenuTypes::Param& param);
    static void removeLayerParam(unsigned int layer);
    static void registLayerObject(unsigned int layer, unsigned int handle);
    static void setShadowLayer(unsigned int layer, bool shadow);
    // a 32-bit return: GfMenuObjBladeRelease::seqSubMenuOpenCustomize passes getLayerGroup + 1 on as an unsigned short
    // without masking it
    static unsigned int getLayerGroup(unsigned int layer);
    // the screen switch's steps (m_switchSeq) and the sub layer's (m_subSeq)
    void switchLayerStart();
    void switchLayerWaitFadeOut();
    void switchLayerWaitRelease();
    void switchLayerOpenScreen();
    void switchLayerWaitScreen();
    void switchLayerWaitFadeIn();
    void subLayerStart();
    void subLayerWaitRelease();
    void subLayerCreate();
    void subLayerWaitOpen();

    bool m_initialized;
    unsigned int m_screen;      // 0x0C: the screen shown; the name is not the original's
    unsigned int m_nextScreen;  // 0x10: the screen being switched to (open sets it); the name is not the original's
    Layer m_layers[4];          // 0x18
    // 0xF8: subLayerStart keeps the layer it closes in its history (the back event clears it); the name is not the
    // original's
    bool m_pushHistory;
    bool m_switching;  // 0xF9: isSwitching's; the name is not the original's
    // 0xFC-0x104: 1.0.0's overrideFadeInFrame, overrideFadeOutFrame and overrideInputBorder set them (the names are
    // not the original's)
    unsigned int m_fadeInTime;
    unsigned int m_fadeOutTime;
    unsigned int m_inputBorder;  // the input manager's minimum layer handle when a switch ends
    bool m_enableEvent;          // 0x108: reciveUIEvent's open, back and close events need it; the name is not the original's
    bool m_fadeOut;              // 0x109: close's/open's first flag; the name is not the original's
    bool m_fadeIn;               // 0x10A: their second flag; the name is not the original's
    mm::mtl::Delegate<void()> m_switchSeq;  // 0x110: the screen switch's current step (postUpdate runs it)
    unsigned int m_nextLayer;               // 0x130: the layer the switch opens; the name is not the original's
    unsigned short m_waitFrames;            // 0x134: switchLayerWaitScreen's frames; the name is not the original's
    mm::mtl::Delegate<void()> m_subSeq;     // 0x138: the sub layer's current step (postUpdate runs it)
    // 0x158: the sub layer to open and its group. One 8-byte value: build zeroes it with one 8-byte store. The
    // names are not the original's.
    struct SubLayer {
        unsigned int m_layer;
        unsigned short m_group;
    };
    SubLayer m_sub;
    ui::UIInputSwitcher m_inputSwitcher;    // 0x160
    mm::mtl::FixedVector<LayerParam, 8> m_layerParams;  // 0x188
};
}  // namespace gf

#endif
