#ifndef CLASSES_UI_UISTREAMMANAGER_H
#define CLASSES_UI_UISTREAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"

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
    // streams the menu image file into a new image object of that name under the parent's object, at that index
    void createImage(const mm::mtl::FixStr<32>& name, unsigned int parent, const char* file, unsigned int index);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its code is in this
    // class's unit next to createImage and takes the same arguments. What it does: createImage's work (the menu
    // image file name, a render resource request, the stream entry), and it also looks the name up among the
    // parent layout's children and, for an image object (RTTI isKindOf), uses that one. Its one caller is
    // GfMenuObjMinimap2::MapListener::reciveEvent, when GfMenuObjUtil::fn_710048FD30(3) holds.
    void fn_710068A034(const mm::mtl::FixStr<32>& name, unsigned int parent, const char* file, unsigned int index);
    // drops the image of that name streamed under the parent's object (GfMenuObjWorldMap::MainListener's floor map)
    void deleteImage(const mm::mtl::FixStr<32>& name, unsigned int parent);

    unsigned char pad_08[0x58];  // 0x60 bytes in all (UIManager's constructor allocates so)
};
}  // namespace ui

#endif
