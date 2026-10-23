#include "gf/GfMenuFlag.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfGameFlag.h"

namespace gf {

void GfMenuFlag::set1(int id, unsigned int value) {
    if (id < 100) {
        GfGameFlag::setLocal(1, id + 39474, value);
    }
}

unsigned int GfMenuFlag::get1(int id) {
    if (id < 100) {
        return GfGameFlag::getLocal(1, id + 39474);
    }
    return 0;
}

void GfMenuFlag::set4(int id, unsigned int value) {
    if (id < 100) {
        GfGameFlag::setLocal(4, id + 534, value);
    }
}

unsigned int GfMenuFlag::get4(int id) {
    if (id < 100) {
        return GfGameFlag::getLocal(4, id + 534);
    }
    return 0;
}

// the destructors and build (0x71003520E8-0x7100352358) are not here yet: see the report

void GfMenuFullScreen::destroy() {
    GfMenuFullScreen* screen = get();
    screen->finalize();
    delete screen;
}

bool GfMenuFullScreen::isInitialized() {
    return get()->m_initialized;
}

// postUpdate through getLayerGroup and the sequence steps are not here yet, except the ones below: see the report

// isOpen (0x7100352BB4) is not here yet: see the report

bool GfMenuFullScreen::isSwitching() {
    GfMenuFullScreen* screen = get();
    if (screen == nullptr) {
        return false;
    }
    if (!screen->m_initialized) {
        return false;
    }
    return screen->m_switching;
}

bool GfMenuFullScreen::setInputObject(unsigned int index, unsigned int handle) {
    GfMenuFullScreen* screen = get();
    if (screen != nullptr) {
        return screen->m_inputSwitcher.setInputObject(index, handle);
    }
    return false;
}

unsigned int GfMenuFullScreen::getInputObject(unsigned int index) {
    GfMenuFullScreen* screen = get();
    if (screen != nullptr) {
        return screen->m_inputSwitcher.getInputObject(index);
    }
    return 0;
}

void GfMenuFullScreen::enableInput(unsigned int index) {
    GfMenuFullScreen* screen = get();
    if (screen != nullptr) {
        screen->m_inputSwitcher.enable(index);
    }
}

void GfMenuFullScreen::disableInput() {
    GfMenuFullScreen* screen = get();
    if (screen != nullptr) {
        screen->m_inputSwitcher.disable();
    }
}

}  // namespace gf
