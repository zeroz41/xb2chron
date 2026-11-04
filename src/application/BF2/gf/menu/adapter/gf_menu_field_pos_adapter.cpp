#include "classes/gf/GfMenuFieldPosAdapter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "gf/GfUtil.h"
#include "mm/Quat.h"
#include "mm/Rect.h"
#include "mm/Vec3.h"
#include "ui/UIUtil.h"
#include <math.h>

namespace gf {

GfMenuFieldPosAdapter::~GfMenuFieldPosAdapter() {
    ;  // the original's body compiled away; clang skips the table store for an empty one
}

GfMenuFieldPosAdapter* GfMenuFieldPosAdapter::create(unsigned int handle, const mm::Vec3& pos, bool keepAdjusted) {
    ui::UIObjectPlugin* plugin = ui::UIObjectPosPlugin::create(handle, 0, 0);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 55
    GfMenuFieldPosAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuFieldPosAdapter(plugin);
    if (adapter != nullptr) {
        adapter->setup(handle, pos, keepAdjusted);
    }
    plugin->release();
    return adapter;
}

GfMenuFieldPosAdapter* GfMenuFieldPosAdapter::create(unsigned int handle, const mm::Vec3& pos) {
    return create(handle, pos, false);
}

void GfMenuFieldPosAdapter::update(const fw::UpdateInfo& info) {
    if (GfGameManager::isGameTypeIra() && m_adjusted) {
        return;
    }
    ui::UIObjectPlugin* plugin = m_plugin;
    if (plugin == nullptr || !plugin->getRTTI()->isKindOf(&ui::UIObjectPosPlugin::m_rtti)) {
        return;
    }
    mm::Vec3 screen;
    bool onScreen = GfGameManager::isGameTypeIra() ? getScreenPos(screen, m_pos, m_keepAdjusted ? !m_offScreen : false)
                                                   : util::getScreenPos(screen, m_pos);
    if (!onScreen || !mm::Quat::isValid(screen.x) || !mm::Quat::isValid(screen.y)) {
        return;
    }
    short y, x;  // declared y first: the 10000 goes to y's register and is copied to x's, as in the original
    x = screen.x;
    y = screen.y;
    if (!m_offScreen) {
        ui::UIObjectAcc acc(m_handle);
        if (acc.m_object != nullptr) {
            if (m_first) {
                x = y = 10000;
                m_first = false;
            } else {
                mm::Rect<short> rect;
                acc.getRect(rect, 2);
                rect.x = x - rect.w / 2;
                rect.y = y - rect.h / 2;
                if (ui::UIUtil::adjustScreen(rect)) {
                    x = rect.x + rect.w / 2;
                    y = rect.y + rect.h / 2;
                    if (m_keepAdjusted) {
                        m_adjusted = true;
                    }
                } else {
                    m_offScreen = true;
                }
            }
        }
    }
    static_cast<ui::UIObjectPosPlugin*>(plugin)->m_pos.x = x;
    static_cast<ui::UIObjectPosPlugin*>(plugin)->m_pos.y = y;
}

bool GfMenuFieldPosAdapter::getScreenPos(mm::Vec3& screen, const mm::Vec3& world, bool behind) {
    if (!behind) {
        return util::getScreenPos(screen, world);
    }
    float x = world.x;
    float y = world.y;
    float z = world.z;
    const mm::Mat44& m = GfInfo::m_viewProj;
    // GfInfo::m_viewProj applied to (x, y, z, 1); unlike util::getScreenPos no depth test and 1/|w|
    float w = fabsf(x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + m.m[3][3]);
    if (w <= 1e-6f) {
        return false;
    }
    float sz = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + m.m[3][2];
    float sy = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + m.m[3][1];
    float sx = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + m.m[3][0];
    float inv = 1.0f / w;
    screen.x = (inv * sx + 1.0f) * (GfInfo::m_camSize.x * 0.5f);
    screen.y = (1.0f - inv * sy) * (GfInfo::m_camSize.y * 0.5f);
    screen.z = inv * sz;
    return true;
}

}  // namespace gf
