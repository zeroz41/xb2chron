#ifndef UI_UIUTIL_H
#define UI_UIUTIL_H

namespace mm { namespace mtl { class IAllocator; } }

namespace ui { class UIObject; }
namespace mm { template <typename> class Rect; }

namespace ui { namespace UIUtil {
mm::mtl::IAllocator* getProgAllocator();
UIObject* getObject(unsigned int handle);
bool isValid(unsigned int handle);
bool adjustScreen(mm::Rect<short>& rect);  // true when it had to move the rectangle onto the screen
unsigned int registObject(UIObject* object);  // the handle its object map gives it
}}  // namespace ui::UIUtil

#endif
