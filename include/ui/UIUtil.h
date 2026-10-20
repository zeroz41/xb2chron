#ifndef UI_UIUTIL_H
#define UI_UIUTIL_H

namespace mm { namespace mtl { class IAllocator; } }

namespace ui { namespace UIUtil {
mm::mtl::IAllocator* getProgAllocator();
}}  // namespace ui::UIUtil

#endif
