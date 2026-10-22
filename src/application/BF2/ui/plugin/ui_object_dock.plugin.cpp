#include "classes/ui/UIObjectPlugin.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectDockPlugin.h"
#include "mm/Mat44.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"

namespace ui {

UIObjectDockPlugin::~UIObjectDockPlugin() {
    ;  // the original stores the table and returns; clang drops the store for an empty body
}

UIObjectDockPlugin* UIObjectDockPlugin::create(unsigned int handle, short x, short y, unsigned int target) {
#line 53
    UIObjectDockPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectDockPlugin(target);
    plugin->addRef();
    if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->m_offset.x = x;
        plugin->m_offset.y = y;
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectDockPlugin::execute(UIObjectAcc& acc) {
    if (!UIUtil::isValid(m_target)) {
        return;
    }
    UIObjectAcc target(m_target);
    if (target.m_object != nullptr && target.isDisp()) {
        short width;
        mm::Pnt<short> pos;
        short height;
        mm::Rect<short> area;
        acc.getSize(true, width, height);
        width /= 2;
        height /= 2;
        {  // the target's rectangle shares its slot with the matrix below: its scope ends here
            mm::Rect<short> rect;
            target.getRect(rect, 2);
            pos.x = rect.x + rect.w / 2;
            pos.y = rect.y + rect.h / 2;
            short sign = m_inside == 0 ? 1 : -1;
            switch (m_side) {
            case 0:
                pos.x = rect.x - width * sign;
                break;
            case 1:
                pos.x += rect.w / 2 + width * sign;
                break;
            case 2:
                pos.y = rect.y - height * sign;
                break;
            case 3:
                pos.y += rect.h / 2 + height * sign;
                break;
            case 4:
                pos.x = rect.x - width * sign;
                pos.y = rect.y - height * sign;
                break;
            case 5:
                pos.x = rect.x - width * sign;
                pos.y += rect.h / 2 + height * sign;
                break;
            case 6:
                pos.x += rect.w / 2 + width * sign;
                pos.y = rect.y - height * sign;
                break;
            case 7:
                pos.x += rect.w / 2 + width * sign;
                pos.y += rect.h / 2 + height * sign;
                break;
            }
            switch (m_align) {
            case 0:
                pos.x += m_offset.x;
                pos.y += m_offset.y;
                break;
            case 1:
                pos.x += m_offset.x;
                pos.y = pos.y - rect.h / 2 + height;
                break;
            case 2:
                pos.x += m_offset.x;
                pos.y = pos.y + rect.h / 2 - height;
                break;
            case 3:
                pos.x = pos.x - rect.w / 2 + width;
                pos.y += m_offset.y;
                break;
            case 4:
                pos.x = pos.x + rect.w / 2 - width;
                pos.y += m_offset.y;
                break;
            }
        }
        // read through a reference: its two halves load apart (the original's loads are 2-byte aligned)
        const mm::Rect<short>& limit = m_area;
        if (limit.w > 0 && limit.h > 0) {
            area.x = pos.x - width;
            area.y = pos.y - height;
            area.w = width * 2;
            area.h = height * 2;
            if (UIUtil::adjustRect(area, m_area)) {
                pos.x = area.x + width;
                pos.y = area.y + height;
            }
        }
        acc.setPosCenter(pos);
        mm::Mat44 matrix;
        target.getMatrix(matrix);
        acc.setMatrix(matrix);
        UIObjectPlugin::execute(acc);
    }
}

bool UIObjectDockPlugin::isNeedUpdate(UIObjectAcc& acc) {
    return acc.isDisp();
}

mm::mtl::RTTI UIObjectDockPlugin::m_rtti("UIObjectDockPlugin", &UIObjectPlugin::m_rtti, nullptr);

}  // namespace ui
