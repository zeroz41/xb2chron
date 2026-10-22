#ifndef UI_UIOBJECTPLUGINUTIL_H
#define UI_UIOBJECTPLUGINUTIL_H

namespace ui { class UIObjectPlugin; }

namespace ui { namespace UIObjectPluginUtil {
// gives the object its plugin; false when it does not take it (each plugin's create then drops its own)
bool attachPlugin(unsigned int handle, UIObjectPlugin* plugin);
}}  // namespace ui::UIObjectPluginUtil

#endif
