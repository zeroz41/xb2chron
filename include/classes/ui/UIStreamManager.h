#ifndef CLASSES_UI_UISTREAMMANAGER_H
#define CLASSES_UI_UISTREAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIStreamManager; }

namespace ui {
// table 0x7100B75460
class UIStreamManager : public ::mm::mtl::PtrSingleton< ::ui::UIStreamManager> {
public:
    virtual ~UIStreamManager();  // slot 0
    // streams the contents' image at index into the object of that handle (UIImageObject::setImageIndex)
    void start(unsigned int contents, unsigned int handle, unsigned int index);
    unsigned int getContentsNum(unsigned int contents);  // the contents' number of images
};
}  // namespace ui

#endif
