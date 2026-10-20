#ifndef CLASSES_UI_UILISTINFO_H
#define CLASSES_UI_UILISTINFO_H

#include "classes/ui/UIListInfoBase.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace ui {
// a template: 11 instances in the module
template <typename T0>
class UIListInfo : public ::ui::UIListInfoBase {
public:
    virtual ~UIListInfo();  // slot 0
    virtual void clear();  // slot 2
    virtual void setup(mm::mtl::IAllocator*, ui::UIListInfoBase::SetupParam const&);  // slot 4
};
}  // namespace ui

#endif
