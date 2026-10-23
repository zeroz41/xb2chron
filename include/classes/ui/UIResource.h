#ifndef CLASSES_UI_UIRESOURCE_H
#define CLASSES_UI_UIRESOURCE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"

namespace fw { class CommonResource; }
namespace mm { namespace mtl { class IAllocator; } }
namespace ui { class UIBuildInfo; }

namespace ui {
// table 0x7100B757F8; counted: its constructor zeroes the count at 0x8, UIFontManager releases it as
// reference_object.h does (`m_RefCount > 0`, then slot 1)
class UIResource : public ::mm::mtl::ReferenceObject {
public:
    UIResource(const char* name);
    virtual ~UIResource();  // slot 0
    void load(const UIBuildInfo* info, mm::mtl::IAllocator* allocator);
    bool isValid() const;
    bool isLoading() const;
    fw::CommonResource* search(const char* name) const;  // the loaded resource of that file name, or null
    mm::mtl::FixStr<32> m_name;  // the constructor's (UIFontManager::update reads the BDAT table of that name)
    unsigned char pad_30[0x78];
};
}  // namespace ui

#endif
