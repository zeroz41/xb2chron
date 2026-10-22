#include "classes/ui/UIObjectPlugin.h"
#include "mm/Col3.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIColorLibrary.h"
#include "classes/ui/UIObjectColorPlugin.h"
#include "ui/UIUtil.h"
#include "mm/Col4.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"

namespace ui {

UIObjectColorPlugin::~UIObjectColorPlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectColorPlugin* UIObjectColorPlugin::create(unsigned int handle) {
#line 45
    UIObjectColorPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectColorPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        acc.getMulColor(plugin->m_color);
        plugin->init(handle);
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectColorPlugin::setMulColor(const mm::Col3& color) {
    m_colorMode = 0;
    if (!m_color.isEqual(color)) {
        m_color = color;
        m_updateFlags |= 1;
    }
}

void UIObjectColorPlugin::setMulColor(const char* name) {
    mm::Col4 color;
    if (UIColorLibrary::get()->find(name, color)) {
        setMulColor(mm::Col3(color.r, color.g, color.b));
    }
}

void UIObjectColorPlugin::setAddColor(const char* name) {
    mm::Col4 color;
    if (UIColorLibrary::get()->find(name, color)) {
        setAddColor(mm::Col3(color.r, color.g, color.b));
    }
}

void UIObjectColorPlugin::setColorMode(unsigned int mode) {
    if (mode < 2) {
        m_colorMode = mode;
    }
}

void UIObjectColorPlugin::setColor(const char* name) {
    switch (m_colorMode) {
    case 0:
        setMulColor(name);
        break;
    case 1:
        setAddColor(name);
        break;
    }
}

void UIObjectColorPlugin::execute(UIObjectAcc& acc) {
    switch (m_colorMode) {
    case 0:
        acc.setMulColor(m_color);
        break;
    case 1:
        acc.setAddColor(m_color);
        break;
    }
    UIObjectDispPlugin::execute(acc);
}

bool UIObjectColorPlugin::isNeedUpdate(UIObjectAcc& acc) {
    return (m_updateFlags & 1) || acc.isDisp() != m_disp || m_fadeCtrl != nullptr || m_followObjHandle != 0;
}

mm::mtl::RTTI UIObjectColorPlugin::m_rtti("UIObjectColorPlugin", &UIObjectDispPlugin::m_rtti, nullptr);

}  // namespace ui
