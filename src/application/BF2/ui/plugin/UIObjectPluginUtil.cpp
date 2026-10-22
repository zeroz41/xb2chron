#include "ui/UIObjectPluginUtil.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIObject.h"

namespace ui {
namespace UIObjectPluginUtil {

bool attachPlugin(unsigned int handle, UIObjectPlugin* plugin) {
    if (UIUtil::isValid(handle)) {
        UIUtil::getObject(handle)->attachPlugin(plugin);
        return true;
    }
    return false;
}

}  // namespace UIObjectPluginUtil
}  // namespace ui
