#ifndef UI_UIUTIL_H
#define UI_UIUTIL_H

namespace mm { namespace mtl { class IAllocator; } }

namespace ui { class UIObject; }

namespace ui { namespace UIUtil {
mm::mtl::IAllocator* getProgAllocator();
UIObject* getObject(unsigned int handle);
unsigned int registObject(UIObject* object);  // the handle its object map gives it
}}  // namespace ui::UIUtil

#endif
