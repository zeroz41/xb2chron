#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "classes/ui/UIObjectWorldPosPlugin.h"
#include "layer/LayerAccObjBase.h"
#include "ui/UIObjectPluginUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIObject.h"
#include "mm/Mat44.h"
#include "ui/UIUtil.h"

namespace ui {

UIObjectWorldPosPlugin::~UIObjectWorldPosPlugin() {
    ;  // the original stores the table before the base's destructor; clang drops the store for an empty body
}

UIObjectWorldPosPlugin* UIObjectWorldPosPlugin::create(unsigned int handle) {
#line 44
    UIObjectWorldPosPlugin* plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectWorldPosPlugin();
    plugin->addRef();
    if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
        layer::LayerAccObjBase acc(UIUtil::getObject(handle)->m_layer);
        acc.setSpace(layer::LAYER_SPACE_TYPE(1));
    } else if (plugin != nullptr) {
        plugin->release();
        plugin = nullptr;
    }
    return plugin;
}

// execute (0x710068737C) is not matched yet

}  // namespace ui
