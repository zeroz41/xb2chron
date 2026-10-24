#ifndef CLASSES_GF_GFMENUFULLSCREEN_H
#define CLASSES_GF_GFMENUFULLSCREEN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIInputSwitcher.h"

namespace gf { class GfMenuFullScreen; }
namespace gf { class GfSetupParam; }
namespace gf { namespace GfMenuTypes { struct Param; }}

namespace gf {
// table 0x7100B5E850
class GfMenuFullScreen : public ::mm::mtl::PtrSingleton< ::gf::GfMenuFullScreen> {
public:
    virtual ~GfMenuFullScreen();  // slot 0
    static void destroy();
    static bool isInitialized();
    // shows a screen (GfMenuManager::openMenu opens screen 2 so)
    static void open(unsigned int screen, bool flag0, bool flag1);
    static void close(bool flag0, bool flag1);
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
    static unsigned short getLayerGroup(unsigned int layer);
    // 1.0.0's: clears m_initialized (3.0.1 has no copy: destroy inlines it)
    void finalize() {
        m_initialized = false;
    }
    bool m_initialized;
    unsigned int m_screen;  // the screen shown (reciveUIEvent's open event sets it); the name is not the original's
    unsigned char pad_10[0xE9];
    bool m_switching;  // isSwitching's; the name is not the original's
    unsigned char pad_FA[0x36];
    unsigned int m_nextScreen;  // the screen being switched to; the name is not the original's
    unsigned char pad_134[0x2C];
    ui::UIInputSwitcher m_inputSwitcher;
    // the fields past it are not known yet
};
}  // namespace gf

#endif
