#ifndef CLASSES_UI_UISTREAMMANAGER_H
#define CLASSES_UI_UISTREAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace mm { namespace mtl { class IAllocator; } }
namespace ui { class UIStreamManager; }

namespace ui {
// table 0x7100B75460
class UIStreamManager : public ::mm::mtl::PtrSingleton< ::ui::UIStreamManager> {
public:
    UIStreamManager(mm::mtl::IAllocator* allocator);  // UIManager's constructor passes the resource allocator
    virtual ~UIStreamManager();  // slot 0
    // streams the contents' image at index into the object of that handle (UIImageObject::setImageIndex)
    void start(unsigned int contents, unsigned int handle, unsigned int index);
    void update(const fw::UpdateInfo& info);
    unsigned int getContentsNum(unsigned int contents);  // the contents' number of images

    unsigned char pad_08[0x58];  // 0x60 bytes in all (UIManager's constructor allocates so)
};
}  // namespace ui

#endif
