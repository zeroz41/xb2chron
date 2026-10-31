#include "gf/GfMenuFlag.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIInputManager.h"
#include "classes/ui/UIManager.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "mm/Col4.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfGameFlag.h"

namespace gf {

namespace {
// the ui layer of each screen (getScreenLayerID's; 1.0.0's convScreenIDToLayerID reads it too)
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009B7B28)
const unsigned int s_screenLayerIDs[8] = {0, 9, 2, 4, 7, 11, 3, 26};
}  // namespace

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

GfMenuFullScreen::~GfMenuFullScreen() {}

// build is not here yet (a candidate a few words off is in the worker notes)

void GfMenuFullScreen::destroy() {
    GfMenuFullScreen* screen = get();
    screen->finalize();
    delete screen;
}

bool GfMenuFullScreen::isInitialized() {
    return get()->m_initialized;
}

void GfMenuFullScreen::postUpdate(const fw::UpdateInfo& info) {
    GfMenuFullScreen* screen = get();
    if (screen != nullptr && screen->m_initialized) {
        if (screen->m_switchSeq.isValid()) {
            screen->m_switchSeq();
        }
        if (screen->m_subSeq.isValid()) {
            screen->m_subSeq();
        }
    }
}

// reciveUIEvent is not here yet (a candidate a few words off is in the worker notes)

void GfMenuFullScreen::close(bool fadeOut, bool fadeIn) {
    GfMenuFullScreen* screen = get();
    if (isDisp()) {
        screen->m_nextScreen = 0;
        screen->m_switchSeq.set(screen, &GfMenuFullScreen::switchLayerStart);
        GfMenuObjCommonText::close();
        screen->m_fadeOut = fadeOut;
        screen->m_fadeIn = fadeIn;
    }
}

void GfMenuFullScreen::switchLayerStart() {
    ui::UIInputManager* input = ui::UIInputManager::get();
    if (input != nullptr) {
        input->m_minimumLayerHandle = ui::UIUtil::getGroupPriority(4);
    }
    for (int i = 0; i < 4; ++i) {
        if (m_layers[i].m_id != 0) {
            ui::UIManager::get()->terminateLayer(m_layers[i].m_id, false);
        }
    }
    if (m_fadeOut) {
        if (m_fadeOutTime == 0) {
            GfMenuFade::setFade(2, 15, mm::Col4::black);
        } else {
            GfMenuFade::setFade(2, m_fadeOutTime, mm::Col4::black);
            m_fadeOutTime = 0;
        }
    }
    m_fadeOut = true;
    m_switchSeq.set(this, &GfMenuFullScreen::switchLayerWaitFadeOut);
}

// subLayerStart is not here yet (a candidate a few words off is in the worker notes)

// open is not here yet (a candidate a few words off is in the worker notes)

// isOpen is not here yet (a candidate a few words off is in the worker notes)

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

unsigned int GfMenuFullScreen::getScreenLayerID(unsigned int screen) {
    if (screen > 7) {
        return 0;
    }
    return s_screenLayerIDs[screen];
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

// registLayerParam is not here yet (a candidate a few words off is in the worker notes)

// getLayerParam is not here yet (a candidate a few words off is in the worker notes)

// removeLayerParam is not here yet (a candidate a few words off is in the worker notes)

void GfMenuFullScreen::removeLayerParam(unsigned int layer) {
    if (layer != 0) {
        GfMenuFullScreen* screen = get();
        if (screen != nullptr) {
            for (LayerParam* it = screen->m_layerParams.begin(); it != screen->m_layerParams.end(); ++it) {
                if (it->m_layer == layer) {
                    screen->m_layerParams.erase(it);
                    return;
                }
            }
        }
    }
}

void GfMenuFullScreen::registLayerObject(unsigned int layer, unsigned int handle) {
    if (layer != 0) {
        GfMenuFullScreen* screen = get();
        if (screen != nullptr) {
            for (int i = 0; i < 4; ++i) {
                if (screen->m_layers[i].m_id == layer) {
                    screen->m_layers[i].m_object = handle;
                    return;
                }
            }
        }
    }
}

void GfMenuFullScreen::setShadowLayer(unsigned int layer, bool shadow) {
    if (layer != 0) {
        GfMenuFullScreen* screen = get();
        if (screen != nullptr) {
            for (int i = 0; i < 4; ++i) {
                if (screen->m_layers[i].m_id == layer) {
                    screen->m_layers[i].m_shadow = shadow;
                    return;
                }
            }
        }
    }
}

// getLayerGroup is not here yet (a candidate a few words off is in the worker notes)

void GfMenuFullScreen::switchLayerWaitFadeOut() {
    if (GfMenuManager::isFading()) {
        return;
    }
    ml::ScnRenderDrSysParmAcc acc;
    if (m_nextScreen == 0) {
        acc.setViewRenderSkip(0, false);
    } else if (GfManager::isExecModeScenarioGame()) {
        acc.setViewRenderSkip(0, true);
    }
    for (int i = 0; i < 4; ++i) {
        if (m_layers[i].m_id != 0) {
            ui::UIManager::get()->releaseLayer(m_layers[i].m_id);
        }
    }
    m_switchSeq.set(this, &GfMenuFullScreen::switchLayerWaitRelease);
    m_inputSwitcher.clearInputObject();
}

void GfMenuFullScreen::switchLayerWaitRelease() {
    for (int i = 0; i < 4; ++i) {
        if (m_layers[i].m_id != 0) {
            return;
        }
    }
    m_switchSeq.set(this, &GfMenuFullScreen::switchLayerOpenScreen);
}

void GfMenuFullScreen::switchLayerOpenScreen() {
    if (m_nextScreen == 0) {
        GfMenuObjOperationInfo::close();
        GfMenuObjCommonText::close();
        resetLayer(0);
        resetLayer(1);
        resetLayer(2);
        resetLayer(3);
        m_layerParams.clear();
    } else {
        unsigned short id = m_nextLayer;
        if (id != 0) {
            ui::UIManager::get()->createLayer(id);
            m_layers[0].m_id = id;
        }
    }
    m_waitFrames = 2;
    m_switchSeq.set(this, &GfMenuFullScreen::switchLayerWaitScreen);
}

void GfMenuFullScreen::switchLayerWaitScreen() {
    if (ui::UIManager::get()->isLoading()) {
        return;
    }
    if (--m_waitFrames != 0) {
        return;
    }
    if (m_fadeIn) {
        if (m_fadeInTime == 0) {
            GfMenuFade::setFade(2, 15, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
        } else {
            GfMenuFade::setFade(2, m_fadeInTime, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
        }
    }
    m_fadeIn = true;
    if (m_nextScreen != 0) {
        m_switchSeq.set(this, &GfMenuFullScreen::switchLayerWaitFadeIn);
    } else {
        m_screen = m_nextScreen;
        m_nextScreen = 0;
        m_nextLayer = 0;
        m_switchSeq.m_invoker = nullptr;
        ui::UIInputManager* input = ui::UIInputManager::get();
        if (input != nullptr) {
            input->m_minimumLayerHandle = 0;
        }
        if (!m_switchSeq.isValid() && !m_subSeq.isValid()) {
            m_switching = false;
        }
        m_pushHistory = true;
    }
}

void GfMenuFullScreen::switchLayerWaitFadeIn() {
    if (GfMenuManager::isFading()) {
        return;
    }
    m_screen = m_nextScreen;
    m_nextScreen = 0;
    m_nextLayer = 0;
    m_switchSeq.m_invoker = nullptr;
    ui::UIInputManager* input = ui::UIInputManager::get();
    if (input != nullptr) {
        if (m_inputBorder == 0) {
            input->m_minimumLayerHandle = ui::UIUtil::getGroupPriority(3);
        } else {
            input->m_minimumLayerHandle = m_inputBorder;
            m_inputBorder = 0;
        }
    }
    if (!m_switchSeq.isValid() && !m_subSeq.isValid()) {
        m_switching = false;
    }
    m_pushHistory = true;
}

void GfMenuFullScreen::subLayerWaitRelease() {
    for (unsigned short i = m_subGroup; i < 4; ++i) {
        if (m_layers[i].m_id != 0) {
            return;
        }
    }
    m_subSeq.set(this, &GfMenuFullScreen::subLayerCreate);
}

// subLayerCreate is not here yet (a candidate a few words off is in the worker notes)

void GfMenuFullScreen::subLayerWaitOpen() {
    if (ui::UIManager::get()->isLoading()) {
        return;
    }
    if (m_subLayer == 0) {
        unsigned long group = m_subGroup;
        if (group != 0) {
            unsigned int object = m_layers[group - 1].m_object;
            if (object != 0) {
                ui::EventData event;
                event.m_type = 0x43;
                event.m_param0 = group;
                ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
            }
        }
    }
    m_subSeq.m_invoker = nullptr;
    m_subLayer = 0;
    m_subGroup = 0;
    ui::UIInputManager* input = ui::UIInputManager::get();
    if (input != nullptr) {
        if (m_inputBorder == 0) {
            input->m_minimumLayerHandle = ui::UIUtil::getGroupPriority(3);
        } else {
            input->m_minimumLayerHandle = m_inputBorder;
            m_inputBorder = 0;
        }
    }
    if (!m_switchSeq.isValid() && !m_subSeq.isValid()) {
        m_switching = false;
    }
    m_pushHistory = true;
}

}  // namespace gf
