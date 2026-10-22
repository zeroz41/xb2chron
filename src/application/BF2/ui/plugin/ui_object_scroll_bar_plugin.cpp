#include "ui/UIUtil.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIObjectScrollBarPlugin.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec2.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"

namespace ui {

UIObjectScrollBarPlugin::~UIObjectScrollBarPlugin() {
    ;  // the original stores the table and returns; clang drops the store for an empty body
}

UIObjectScrollBarPlugin* UIObjectScrollBarPlugin::create(unsigned int handle, unsigned int direction,
                                                         const UIListInfoBase* listInfo, const char* track) {
    if (listInfo == nullptr || track == nullptr) {
        return nullptr;
    }
#line 50
    UIObjectScrollBarPlugin* plugin =
        new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectScrollBarPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.m_object != nullptr && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        plugin->m_listInfo = listInfo;
        plugin->m_track = acc.searchSibiling(track);
        plugin->m_direction = direction;
        acc.getPos(plugin->m_pos);
        acc.getScale(plugin->m_scale);
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

void UIObjectScrollBarPlugin::setScaleEnable(bool enable) {
    m_scaleEnable = enable;
}

void UIObjectScrollBarPlugin::execute(UIObjectAcc& acc) {
    UIObjectAcc track(m_track);
    if (m_direction == 0) {
        if (m_listInfo->getRowSize() > m_listInfo->getPageRowSize()) {
            acc.setDisp(true);
            track.setDisp(true);
            if (m_scaleEnable) {
                float rate = (float)m_listInfo->getPageRowSize() / (float)m_listInfo->getRowSize();
                acc.setScale(mm::Vec2(1.0f, m_scale.y * rate));
                mm::Rect<short> rect;
                acc.getRect(rect, 2);
                if (rect.h <= 1) {
                    acc.getRect(rect, 0);
                    rate = 2.0f / rect.h;  // at least two pixels tall
                    acc.setScale(mm::Vec2(1.0f, m_scale.y * rate));
                }
            }
            short width;
            short height;
            acc.getSize(true, width, height);
            short trackWidth;
            short trackHeight;
            track.getSize(true, trackWidth, trackHeight);
            int range = trackHeight - height;
            if (!m_scaleEnable) {
                mm::Pnt<short> trackPos;
                track.getPos(trackPos);
                range = trackPos.y + range - m_pos.y;
            }
            float step = (float)range / (float)(m_listInfo->getRowSize() - m_listInfo->getPageRowSize());
            short y = m_pos.y + (unsigned int)(step * m_listInfo->getRowOffset());
            acc.setPos(mm::Pnt<short>(m_pos.x, y));
        } else {
            acc.setDisp(false);
            track.setDisp(false);
        }
    }
    UIObjectPlugin::execute(acc);
}

}  // namespace ui
