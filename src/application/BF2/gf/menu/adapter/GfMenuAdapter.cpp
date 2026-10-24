#include "mm/mtl/IntrusiveList.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuRewriteNumber.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "classes/ui/UIObjectWorldPosPlugin.h"
#include "classes/ui/UIObjectOffsetPlugin.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "classes/ui/UIObjectColorPlugin.h"
#include "classes/ui/UIObjectPatternPlugin.h"
#include "ui/UIStr.h"
#include "mm/Col3.h"
#include "mm/Pnt.h"
#include "mm/Vec3.h"
#include <string.h>

namespace gf {

GfMenuAdapter::GfMenuAdapter(ui::UIObjectPlugin* plugin, bool managerFlag, bool changed)
    : m_plugin(nullptr), m_flags(0), m_rowHandle(0), m_rewriteNumber(nullptr) {
    plugin->addRef();
    m_plugin = plugin;
    m_flags = m_flags | (changed ? 3 : 1);
    GfMenuAdapterManager::get()->addAdapter(this, managerFlag);
}

GfMenuAdapter::~GfMenuAdapter() {
    if (m_plugin != nullptr) {
        m_plugin->release();
        m_plugin = nullptr;
    }
    if (m_rewriteNumber != nullptr) {
        m_rewriteNumber->release();
        m_rewriteNumber = nullptr;
    }
}

void GfMenuAdapter::setChange() {
    m_flags |= 1;
    if (m_plugin != nullptr) {
        m_plugin->m_updateFlags |= 2;
    }
}

ui::UIObjectPlugin* GfMenuAdapter::createPlugin(unsigned int handle, const PluginSetup& setup) {
    ui::UIObjectAcc acc(handle);
    ui::UIObjectPlugin* plugin = nullptr;
    if (acc.m_object != nullptr) {
        switch (setup.m_type) {
        case 0: {
            ui::UIObjectNumberPlugin* number = ui::UIObjectNumberPlugin::create(handle);
            if (number != nullptr) {
                number->setMin(setup.m_min);
                number->setMax(setup.m_max);
            }
            plugin = number;
            break;
        }
        case 1:
            if (acc.isImage()) {
                ui::UIObjectNumberPlugin* number = ui::UIObjectNumberPlugin::create(handle);
                if (number != nullptr) {
                    int min = acc.isStreamImage();
                    int max = min + acc.getImageMax();
                    number->setMin(min);
                    number->setMax(max);
                }
                plugin = number;
            }
            break;
        case 2:
            plugin = ui::UIObjectTextPlugin::create(handle);
            break;
        case 3:
            plugin = ui::UIObjectDispPlugin::create(handle);
            break;
        case 4:
            plugin = ui::UIObjectPosPlugin::create(handle, 0, 0);
            break;
        case 5:
            plugin = ui::UIObjectWorldPosPlugin::create(handle);
            break;
        case 6:
            plugin = ui::UIObjectOffsetPlugin::create(handle);
            break;
        case 7:
            plugin = ui::UIObjectTimePlugin::create(handle, setup.m_min);
            break;
        case 8:
            plugin = ui::UIObjectColorPlugin::create(handle);
            break;
        case 9:
            plugin = ui::UIObjectPatternPlugin::create(handle);
            break;
        }
    }
    return plugin;
}

void GfMenuAdapter::setDispAlphaMode(bool on) {
    if (ui::UIObjectDispPlugin* disp = getPlugin<ui::UIObjectDispPlugin>()) {
        disp->setAlphaMode(on);
    }
}

void GfMenuAdapter::setDispReverseMode(bool on) {
    if (ui::UIObjectDispPlugin* disp = getPlugin<ui::UIObjectDispPlugin>()) {
        disp->setReverseMode(on);
    }
}

void GfMenuAdapter::setDispFadeMode(float time) {
    if (ui::UIObjectDispPlugin* disp = getPlugin<ui::UIObjectDispPlugin>()) {
        disp->setFadeMode(time);
    }
}

void GfMenuAdapter::setDispSuspendMode(bool on) {
    if (ui::UIObjectDispPlugin* disp = getPlugin<ui::UIObjectDispPlugin>()) {
        disp->setSuspendMode(true);
    }
}

void GfMenuAdapter::setNumberReverseMode(bool on) {
    if (ui::UIObjectNumberPlugin* number = getPlugin<ui::UIObjectNumberPlugin>()) {
        number->m_reverse = on;
    }
}

void GfMenuAdapter::setNumberInterpolateMode(float interpolate) {
    if (ui::UIObjectNumberPlugin* number = getPlugin<ui::UIObjectNumberPlugin>()) {
        number->setInterpolate(interpolate);
    }
}

void GfMenuAdapter::setPosAdjustScreen(bool on) {
    if (ui::UIObjectPosPlugin* pos = getPlugin<ui::UIObjectPosPlugin>()) {
        pos->m_screenAdjust = on;
    }
}

void GfMenuAdapter::setPosAdjustSize(unsigned int width, unsigned int height) {
    if (ui::UIObjectPosPlugin* pos = getPlugin<ui::UIObjectPosPlugin>()) {
        pos->m_adjustWidth = width;
        pos->m_adjustHeight = height;
    }
}

void GfMenuAdapter::setPosAdjustSizeOffs(short width, short height) {
    if (ui::UIObjectPosPlugin* pos = getPlugin<ui::UIObjectPosPlugin>()) {
        pos->m_adjustMarginWidth = width;
        pos->m_adjustMarginHeight = height;
    }
}

void GfMenuAdapter::setPosOffsMode(unsigned int mode) {
    if (ui::UIObjectPosPlugin* pos = getPlugin<ui::UIObjectPosPlugin>()) {
        pos->m_anchor = mode;
    }
}

void GfMenuAdapter::setOffsetLimit(unsigned short x, unsigned short y) {
    if (ui::UIObjectOffsetPlugin* offset = getPlugin<ui::UIObjectOffsetPlugin>()) {
        offset->m_limit.x = x;
        offset->m_limit.y = y;
    }
}

int GfMenuAdapter::getNumber() const {
    if (ui::UIObjectNumberPlugin* number = getPlugin<ui::UIObjectNumberPlugin>()) {
        return number->m_number;
    }
    return 0;
}

int GfMenuAdapter::getNumberMax() const {
    if (ui::UIObjectNumberPlugin* number = getPlugin<ui::UIObjectNumberPlugin>()) {
        return number->m_max;
    }
    return 0;
}

void GfMenuAdapter::setRewriteNumber(GfMenuRewriteNumber* rewrite) {
    m_rewriteNumber = rewrite;
    rewrite->addRef();
}

void GfMenuAdapter::setNumber(int number) {
    if (ui::UIObjectNumberPlugin* plugin = getPlugin<ui::UIObjectNumberPlugin>()) {
        if (m_rewriteNumber != nullptr && m_rewriteNumber->m_enabled) {
            number = m_rewriteNumber->m_number;
        }
        plugin->setNumber(number);
    }
}

void GfMenuAdapter::setNumberMin(int min) {
    if (ui::UIObjectNumberPlugin* number = getPlugin<ui::UIObjectNumberPlugin>()) {
        number->setMin(min);
    }
}

void GfMenuAdapter::setNumberMax(int max) {
    if (ui::UIObjectNumberPlugin* number = getPlugin<ui::UIObjectNumberPlugin>()) {
        number->setMax(max);
    }
}

void GfMenuAdapter::setText(const ui::UIStr& text) {
    if (ui::UIObjectTextPlugin* plugin = getPlugin<ui::UIObjectTextPlugin>()) {
        plugin->setText(text);
    }
}

void GfMenuAdapter::setDisp(bool disp) {
    if (ui::UIObjectDispPlugin* plugin = getPlugin<ui::UIObjectDispPlugin>()) {
        plugin->setDisp(disp);
        if (m_rowHandle != 0) {
            ui::UIObjectAcc acc(m_rowHandle);
            acc.setDisp(disp);
        }
    }
}

void GfMenuAdapter::setPos(const mm::Pnt<short>& pos) {
    if (ui::UIObjectPosPlugin* plugin = getPlugin<ui::UIObjectPosPlugin>()) {
        plugin->m_pos = pos;
    }
}

void GfMenuAdapter::setPosWorld(const mm::Vec3& pos) {
    if (ui::UIObjectWorldPosPlugin* plugin = getPlugin<ui::UIObjectWorldPosPlugin>()) {
        plugin->m_worldPos = pos;
    }
}

void GfMenuAdapter::setOffsetTargetPos(const mm::Pnt<short>& pos) {
    if (ui::UIObjectOffsetPlugin* plugin = getPlugin<ui::UIObjectOffsetPlugin>()) {
        plugin->m_target = pos;
    }
}

bool GfMenuAdapter::isPosScreenAdjust() const {
    if (ui::UIObjectPosPlugin* plugin = getPlugin<ui::UIObjectPosPlugin>()) {
        return plugin->m_screenAdjust;
    }
    return false;
}

void GfMenuAdapter::setMulColor(const char* color) {
    if (ui::UIObjectColorPlugin* plugin = getPlugin<ui::UIObjectColorPlugin>()) {
        if (color != nullptr) {
            plugin->setMulColor(color);
        } else {
            plugin->setMulColor(mm::Col3(1.0f, 1.0f, 1.0f));
        }
    }
}

void GfMenuAdapter::setAddColor(const char* color) {
    if (ui::UIObjectColorPlugin* plugin = getPlugin<ui::UIObjectColorPlugin>()) {
        plugin->setAddColor(color == nullptr ? "" : color);
    }
}

void GfMenuAdapter::setColorMode(unsigned int mode) {
    if (ui::UIObjectColorPlugin* plugin = getPlugin<ui::UIObjectColorPlugin>()) {
        plugin->setColorMode(mode);
    }
}

void GfMenuAdapter::setColor(const char* color) {
    ui::UIObjectColorPlugin* plugin = getPlugin<ui::UIObjectColorPlugin>();
    if (color != nullptr && plugin != nullptr) {
        plugin->setColor(color);
    }
}

void GfMenuAdapter::setTextFacePattern(const char* pattern) {
    ui::UIObjectPatternPlugin* plugin = getPlugin<ui::UIObjectPatternPlugin>();
    if (pattern != nullptr && plugin != nullptr) {
        plugin->setFacePattern(pattern);
    }
}

void GfMenuAdapter::update(const fw::UpdateInfo& info) {
    m_flags &= ~1;
}

}  // namespace gf
