#include "classes/ui/UIObjectPlugin.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectArrangePlugin.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIObjectPluginUtil.h"

namespace ui {

UIObjectArrangePlugin::UIObjectArrangePlugin() : pad_7C(true) {}

UIObjectArrangePlugin::~UIObjectArrangePlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectArrangePlugin* UIObjectArrangePlugin::create(unsigned int handle) {
#line 45
    UIObjectArrangePlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectArrangePlugin();
    plugin->addRef();
    if (!UIObjectPluginUtil::attachPlugin(handle, plugin) && plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

mm::mtl::RTTI UIObjectArrangePlugin::m_rtti("UIObjectArrangePlugin", &UIObjectDispPlugin::m_rtti, nullptr);

}  // namespace ui
