#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/UIStr.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "ui/UIObjectPluginUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectTextPlugin::~UIObjectTextPlugin() {}

UIObjectTextPlugin* UIObjectTextPlugin::create(unsigned int handle) {
#line 44
    UIObjectTextPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectTextPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr && acc.isText() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->init(handle);
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectTextPlugin::setText(const UIStr& text) {
    if (text.isValid() && !m_text.compare(text)) {
        m_text.copy(text);
        m_updateFlags |= 1;
    }
}

void UIObjectTextPlugin::execute(UIObjectAcc& acc) {
    if (m_text.isValid()) {
        acc.setText(m_text);
    }
    UIObjectDispPlugin::execute(acc);
}

bool UIObjectTextPlugin::isNeedUpdate(UIObjectAcc& acc) {
    if (m_updateFlags & 1) {
        return true;
    }
    if (acc.isDisp() != m_disp) {
        return true;
    }
    if (m_fadeUpdater.m_ctrl != nullptr) {
        return true;
    }
    return m_followObjHandle != 0;
}

mm::mtl::RTTI UIObjectTextPlugin::m_rtti("UIObjectTextPlugin", &UIObjectDispPlugin::m_rtti, nullptr);

}  // namespace ui
