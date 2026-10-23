#include "classes/gf/GfMenuHUD.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

// initialize (0x7100353630) is not here yet: see the report

GfMenuHUD::~GfMenuHUD() {}

// build (0x71003537D8) is not here yet: see the report

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

// fn_7100353934 is not here yet: see the report

void GfMenuHUD::systemWait() {
    m_system.set(this, &GfMenuHUD::systemUpdate);
}

void GfMenuHUD::systemUpdate() {}

// fn_7100353A04 and fn_7100353A94 are not here yet: see the report

}  // namespace gf
