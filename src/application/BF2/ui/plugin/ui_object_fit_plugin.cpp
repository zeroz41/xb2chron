#include "ui/UIUtil.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectFitPlugin.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec2.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"

namespace ui {

UIObjectFitPlugin::~UIObjectFitPlugin() {
    ;  // the original stores the table and returns; clang drops the store for an empty body
}

UIObjectFitPlugin* UIObjectFitPlugin::create(unsigned int handle, unsigned int target, unsigned short marginWidth,
                                             unsigned short marginHeight) {
#line 52
    UIObjectFitPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectFitPlugin();
    plugin->addRef();
    if (UIUtil::isValid(handle) && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->m_marginWidth = marginWidth;
        plugin->m_marginHeight = marginHeight;
        plugin->m_target = target;
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectFitPlugin::execute(UIObjectAcc& acc) {
    UIObjectAcc target(m_target);
    mm::Rect<short> rect;
    short width;
    short height;
    acc.getSize(false, width, height);
    target.getRect(rect, 2);
    unsigned short marginWidth = m_marginWidth;
    unsigned short marginHeight = m_marginHeight;
    if (m_flags.addHalfSize) {
        marginWidth += width / 2;
        marginHeight += height / 2;
    }
    rect.x -= marginWidth;
    rect.y -= marginHeight;
    rect.w += marginWidth * 2;
    rect.h += marginHeight * 2;
    if (rect.w < m_minWidth) {
        rect.x -= (m_minWidth - rect.w) / 2;
        rect.w = m_minWidth;
    }
    if (rect.h < m_minHeight) {
        rect.y -= (m_minHeight - rect.h) / 2;
        rect.h = m_minHeight;
    }
    {
        mm::Vec2 scale;
        acc.getScale(scale);
        float x = m_flags.keepScaleX ? scale.x : (float)(rect.w + m_offsetWidth) / (float)width;
        float y = m_flags.keepScaleY ? scale.y : (float)(rect.h + m_offsetHeight) / (float)height;
        scale = mm::Vec2(x, y);
        acc.setScale(scale);
    }
    rect.x += rect.w / 2 + m_offsetWidth / 2;
    rect.y += rect.h / 2 + m_offsetHeight / 2;
    mm::Pnt<short> pos(rect.x, rect.y);
    acc.setPosCenter(pos);
    UIObjectPlugin::execute(acc);
}

bool UIObjectFitPlugin::isNeedUpdate(UIObjectAcc& acc) {
    return acc.isDisp();
}

mm::mtl::RTTI UIObjectFitPlugin::m_rtti("UIObjectFitPlugin", &UIObjectPlugin::m_rtti, nullptr);

}  // namespace ui
