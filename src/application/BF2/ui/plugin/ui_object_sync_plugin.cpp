#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "classes/ui/UIObjectSyncPlugin.h"
#include "ui/UIObjectPluginUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectSyncPlugin::~UIObjectSyncPlugin() {
    ;  // the original stores the table; clang drops the store for an empty body
}

UIObjectSyncPlugin* UIObjectSyncPlugin::create(unsigned int handle) {
#line 45
    UIObjectSyncPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectSyncPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.m_object == nullptr || !UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        if (plugin != nullptr) {
            plugin->release();
            plugin = nullptr;
        }
    }
    return plugin;
}

void UIObjectSyncPlugin::setTargetObject(unsigned int handle) {
    m_targetObject = handle;
}

void UIObjectSyncPlugin::setTargetFlag(unsigned int flag) {
    m_targetFlag = flag;
}

void UIObjectSyncPlugin::execute(UIObjectAcc& acc) {
    UIObjectAcc target(m_targetObject);
    if (target.m_object != nullptr && m_targetFlag != 0) {
        if (m_targetFlag & SYNC_POS) {
            mm::Pnt<short> pos;
            target.getPos(pos);
            acc.setPos(pos);
        } else if (m_targetFlag & SYNC_POS_CENTER) {
            mm::Pnt<short> pos;
            target.getPosCenter(pos);
            acc.setPosCenter(pos);
        }
        if (m_targetFlag & SYNC_SCALE) {
            mm::Vec2 scale;
            target.getScale(scale);
            acc.setScale(scale);
        }
        if (m_targetFlag & SYNC_ROT) {
            float rot;
            target.getRot(rot);
            acc.setRot(rot);
        }
        if (m_targetFlag & SYNC_ALPHA) {
            float alpha;
            target.getAlpha(alpha);
            acc.setAlpha(alpha);
        }
        if (m_targetFlag & SYNC_DISP) {
            acc.setDisp(target.isDisp());
        }
        if (m_targetFlag & SYNC_DISP_INVERSE) {
            acc.setDisp(!target.isDisp());
        }
    }
    UIObjectPlugin::execute(acc);
}

mm::mtl::RTTI UIObjectSyncPlugin::m_rtti("UIObjectSyncPlugin", &UIObjectPlugin::m_rtti, nullptr);

}  // namespace ui
