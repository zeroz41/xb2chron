#include "classes/gf/GfMenuHUD.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/ui/UIManager.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"

namespace gf {

void GfMenuHUD::initialize(const GfSetupParam& param) {
    m_initialized = true;
    finalize();
    if (ui::UIUtil::isEnableExpType(3) && GfGameManager::isGameTypeIra()) {
        m_layerType = 3;
    }
    m_system.set(this, &GfMenuHUD::systemStart);
    unsigned char* fp = ui::UIUtil::getLayerBdat(m_layerType);
    if (fp != nullptr) {
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            int id = Bdat::getIdTop(fp) + i;
            unsigned char group = Bdat::getVal(fp, "group", id);
            if (group < 3 || group == 4) {
                ui::UIManager::sys()->createLayer(id);
            }
        }
    }
    if (m_layerType == 0 && ui::UIUtil::isEnableExpType(1)) {
        addExpansionLayer(1);
    }
}

GfMenuHUD::~GfMenuHUD() {}

void GfMenuHUD::build(const GfSetupParam& param) {
#line 75
    GfMenuHUD* hud = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuHUD;
    hud->initialize(param);
}

void GfMenuHUD::destroy() {
    GfMenuHUD* hud = get();
    hud->finalize();
    delete hud;
}

bool GfMenuHUD::isInitialized() {
    return get()->m_initialized;
}

void GfMenuHUD::postUpdate(const fw::UpdateInfo& info) {
    GfMenuHUD* hud = get();
    if (hud != nullptr && hud->m_initialized) {
        if (hud->m_system.isValid()) {
            hud->m_system();
        }
        if (hud->m_scene.isValid()) {
            hud->m_scene();
        }
    }
}

void GfMenuHUD::reciveUIEvent(const ui::EventData& event, unsigned int handle) {}

void GfMenuHUD::systemStart() {
    m_system.set(this, &GfMenuHUD::systemWait);
}

void GfMenuHUD::addExpansionLayer(unsigned int type) {
    unsigned char* fp = ui::UIUtil::getLayerBdat(type);
    if (fp == nullptr) {
        return;
    }
    GfMenuAdapterManager::cleanup();
    for (int i = 0; i < Bdat::getIdCount(fp); i++) {
        int id = Bdat::getIdTop(fp) + i;
        unsigned char group = Bdat::getVal(fp, "group", id);
        if (group < 3 || group == 4) {
            ui::UIManager::sys()->createLayerEx(fp, id, true);
        }
    }
}

void GfMenuHUD::systemWait() {
    m_system.set(this, &GfMenuHUD::systemUpdate);
}

void GfMenuHUD::systemUpdate() {}

void GfMenuHUD::systemSwitchExpLayer() {
    for (WaitObject* it = m_waitObjects.begin(); it != m_waitObjects.end(); ++it) {
        if (ui::UIManager::sys()->searchObject(it->m_name, it->m_id) != 0) {
            return;
        }
    }
    m_waitObjects.clear();
    addExpansionLayer(m_layerType);
    m_system.set(this, &GfMenuHUD::systemUpdate);
}

// switchExpansionLayer is not here yet

}  // namespace gf
