#include "ui/UIUtil.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "mm/Pnt.h"
#include "classes/ui/UITransform.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"

namespace ui {

// UIObjectPluginUtil::attachPlugin (0x7100685F44) is ui_object_plugin_util.cpp's: create calls it, not inlined

UIObjectPosPlugin::UIObjectPosPlugin()
    : m_pos(0, 0), m_screenAdjust(false), m_adjustWidth(0), m_adjustHeight(0), m_adjustMarginWidth(0),
      m_adjustMarginHeight(0), m_anchor(0), m_screenAdjusting(false) {}

UIObjectPosPlugin::~UIObjectPosPlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectPosPlugin* UIObjectPosPlugin::create(unsigned int handle, short x, short y) {
#line 49
    UIObjectPosPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectPosPlugin();
    plugin->addRef();
    if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->m_pos.x = x;
        plugin->m_pos.y = y;
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectPosPlugin::execute(UIObjectAcc& acc) {
    UIObjectDispPlugin::execute(acc);
    if (!acc.isDisp()) {
        return;
    }
    mm::Rect<short> rect;
    mm::Pnt<short> pos = m_pos;
    acc.getRect(rect, 2);
    switch (m_anchor) {
    case 1:
        pos.y -= rect.h / 2;
        break;
    case 2:
        pos.y += rect.h / 2;
        break;
    case 3:
        pos.x -= rect.w / 2;
        break;
    case 4:
        pos.x += rect.w / 2;
        break;
    }
    if (m_screenAdjust) {
        mm::Rect<short> area = rect;
        if (m_adjustWidth == 0 && m_adjustHeight == 0) {
            area.w = m_adjustMarginWidth + rect.w;
            area.h = m_adjustMarginHeight + rect.h;
            area.x = pos.x - area.w / 2;
            area.y = pos.y - area.h / 2;
        } else {
            area.x = pos.x - rect.w / 2;
            area.y = pos.y - rect.h / 2;
            area.x += (rect.w - m_adjustWidth) / 2;
            area.y += (rect.h - m_adjustHeight) / 2;
            area.w = m_adjustWidth;
            area.h = m_adjustHeight;
        }
        m_screenAdjusting = UIUtil::adjustScreen(area);
        pos.x = area.x + area.w / 2;
        pos.y = area.y + area.h / 2;
        acc.setScreenAdjusting(m_screenAdjusting);
    }
    acc.setPosCenter(pos);
}

mm::mtl::RTTI UIObjectPosPlugin::m_rtti("UIObjectPosPlugin", &UIObjectDispPlugin::m_rtti, nullptr);

}  // namespace ui
