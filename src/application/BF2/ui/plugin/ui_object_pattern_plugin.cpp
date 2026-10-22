#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIFontManager.h"
#include "classes/ui/UIObjectPatternPlugin.h"
#include "ui/UIObjectPluginUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectPatternPlugin::~UIObjectPatternPlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectPatternPlugin* UIObjectPatternPlugin::create(unsigned int handle) {
#line 44
    UIObjectPatternPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectPatternPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->m_facePattern = acc.getTextFacePatternIndex();
        plugin->init(handle);
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectPatternPlugin::setFacePattern(const char* name) {
    if (name != nullptr) {
        unsigned int index;
        if (UIFontManager::sys()->findFacePattern(name, index) && m_facePattern != index) {
            m_facePattern = index;
            m_updateFlags |= 1;
        }
    }
}

void UIObjectPatternPlugin::execute(UIObjectAcc& acc) {
    acc.setTextFacePattern(m_facePattern);
    UIObjectDispPlugin::execute(acc);
}

bool UIObjectPatternPlugin::isNeedUpdate(UIObjectAcc& acc) {
    if (m_updateFlags & 1) {
        return true;
    }
    if (acc.isDisp() != m_disp) {
        return true;
    }
    if (m_fadeCtrl != nullptr) {
        return true;
    }
    return m_followObjHandle != 0;
}

}  // namespace ui
