#ifndef CLASSES_UI_UILAYOUTDATA_H
#define CLASSES_UI_UILAYOUTDATA_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace mm { template <typename> class Rect; }
namespace ui { class UIObject; }

namespace ui {
// table 0x7100B74CB0; a layout binary's positions, looked up by name (in its parent's when it has none of that name)
class UILayoutData : public ::mm::mtl::ReferenceObject {
public:
    UILayoutData(void* binary, const UILayoutData* parent) {
        addRef();  // create's caller holds this reference
        m_binary = binary;
        m_parent = parent;
    }
    virtual ~UILayoutData();  // slot 0
    static UILayoutData* create(void* binary, mm::mtl::IAllocator* allocator, const UILayoutData* parent);
    bool attachLayout(const char* name, UIObject* object) const;
    bool getLayoutRect(const char* name, mm::Rect<short>& rect) const;
    void* m_binary;                 // create's: the layout binary
    const UILayoutData* m_parent;   // create's: searched for a name this one lacks
};
}  // namespace ui

#endif
