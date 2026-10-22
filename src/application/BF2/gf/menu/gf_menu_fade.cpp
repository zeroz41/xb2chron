#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObjFade.h"
#include "mm/Col4.h"
#include "ui/EventData.h"

namespace gf {

GfMenuFade::~GfMenuFade() {}

// build (0x7100350098) is not matched yet: it calls fn_710068F188, which 1.0.0's callers call as
// UIManager::createLayer, but 3.0.1 moved that body into fn_710068F208 behind it

void GfMenuFade::destroy() {
    GfMenuFade* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuFade::finalize() {
    m_initialized = false;
}

bool GfMenuFade::isInitialized() {
    GfMenuFade* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuFade::setFade(unsigned int channel, unsigned int time, const mm::Col4& color) {
    GfMenuFade* menu = get();
    if (menu == nullptr) {
        return;
    }
    mm::Col4 col;
    col.a = color.a;
    float b, g, r;  // the current colour's when the new one has no alpha (none while the menu is not ready)
    if (color.a == 0.0f) {
        if (menu->m_initialized) {
            mm::Col4 current;
            GfMenuObjFade::getFadeColor(channel, current);
            r = current.r;
            g = current.g;
            b = current.b;
        }
    } else {
        r = color.r;
        g = color.g;
        b = color.b;
    }
    col.r = r;
    col.g = g;
    col.b = b;
    GfMenuObjFade::StartParam param;
    param.time = time;
    param.channel = channel;
    param.color = col;
    GfMenuObjFade::start(param);
    menu->m_fading[channel] = true;
}

void GfMenuFade::getFadeColor(unsigned int channel, mm::Col4& color) {
    GfMenuFade* menu = get();
    if (menu != nullptr && menu->m_initialized) {
        GfMenuObjFade::getFadeColor(channel, color);
    }
}

void GfMenuFade::setLoading(unsigned int id, bool disp) {
    GfMenuObjFade::dispLoading(disp, id);
}

bool GfMenuFade::isFading(unsigned int channel) {
    GfMenuFade* menu = get();
    if (channel <= 2 && menu != nullptr) {
        return menu->m_fading[channel];
    }
    return false;
}

void GfMenuFade::reciveEvent(const ui::EventData& event, unsigned int handle) {
    GfMenuFade* menu = get();
    if (menu == nullptr) {
        return;
    }
    switch (event.m_type) {
    case 5:
        if (event.m_param1 == 1) {
            menu->m_initialized = true;
        }
        break;
    case 0xA:
        if (event.m_param0 <= 2) {
            menu->m_fading[event.m_param0] = true;
        }
        break;
    case 0xB:
        if (event.m_param0 <= 2) {
            menu->m_fading[event.m_param0] = false;
        }
        break;
    }
}

}  // namespace gf
