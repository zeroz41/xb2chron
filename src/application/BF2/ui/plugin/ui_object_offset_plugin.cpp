#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Math.h"
#include "classes/ui/UIObjectOffsetPlugin.h"
#include "ui/UIObjectPluginUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectOffsetPlugin::~UIObjectOffsetPlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectOffsetPlugin* UIObjectOffsetPlugin::create(unsigned int handle) {
#line 42
    UIObjectOffsetPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectOffsetPlugin();
    plugin->addRef();
    if (!UIObjectPluginUtil::attachPlugin(handle, plugin) && plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectOffsetPlugin::execute(UIObjectAcc& acc) {
    UIObjectPlugin::execute(acc);
    if (acc.isDisp()) {
        mm::Rect<short> rect;
        acc.getRect(rect, 3);
        int limitX = m_limit.x;
        int limitY = m_limit.y;
        short dx = 0;
        if (limitX != 0) {
            dx = m_target.x - (rect.x + rect.w / 2);
            if (limitX < mm::abs(dx)) {
                dx = (dx < 0 ? -1 : 1) * limitX;
            }
        }
        short dy = 0;
        if (limitY != 0) {
            dy = m_target.y - (rect.y + rect.h / 2);
            if (limitY < mm::abs(dy)) {
                dy = (dy < 0 ? -1 : 1) * limitY;
            }
        }
        mm::Pnt<short> pos;
        acc.getPosCenter(pos);
        pos.x += dx;
        pos.y += dy;
        acc.setPosCenter(pos);
        if (acc.isDebugDraw()) {
        }
    }
}

mm::mtl::RTTI UIObjectOffsetPlugin::m_rtti("UIObjectOffsetPlugin", &UIObjectDispPlugin::m_rtti, nullptr);

}  // namespace ui
