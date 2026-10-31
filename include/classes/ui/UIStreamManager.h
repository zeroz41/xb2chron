#ifndef CLASSES_UI_UISTREAMMANAGER_H
#define CLASSES_UI_UISTREAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; class CommonResource; class RenderResource; }
namespace mm { namespace mtl { class IAllocator; } }
namespace ui { class UIStreamManager; }

namespace ui {
// table 0x7100B75460
class UIStreamManager : public ::mm::mtl::PtrSingleton< ::ui::UIStreamManager> {
public:
    UIStreamManager(mm::mtl::IAllocator* allocator);  // UIManager's constructor passes the resource allocator
    virtual ~UIStreamManager();  // slot 0
    // streams the contents' image at index into the object of that handle (UIImageObject::setImageIndex)
    // the id of a bdat of stream images, registered on first sight
    unsigned int regist(unsigned char* bdat);
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

    // a registered bdat of stream images (regist): the id is the crc of its sheet name (the names are not the
    // original's)
    struct Contents : public ::mm::mtl::IntrusiveListNodeBase {
        unsigned int m_id;
        unsigned char* m_bdat;
    };
    // the image object of a handle start streams into, with the resource it holds (the names are not the
    // original's)
    struct Stream : public ::mm::mtl::IntrusiveListNodeBase {
        unsigned int m_handle;
        fw::CommonResource* m_resource;
    };
    // an image object createImage makes under a parent's object (the names are not the original's)
    struct Image : public ::mm::mtl::IntrusiveListNodeBase {
        unsigned int m_parent;
        unsigned int pad_14;
        mm::mtl::FixStr<32> m_name;
        unsigned int m_index;
        fw::RenderResource* m_resource;  // the shown one
        fw::RenderResource* m_request;  // the one loading (createImage requests it)
        bool m_requested;
    };

    mm::mtl::IAllocator* m_allocator;  // the constructor's (the names are not the original's)
    mm::mtl::IntrusiveList<Contents> m_contents;
    mm::mtl::IntrusiveList<Stream> m_streams;
    mm::mtl::IntrusiveList<Image> m_images;
    fw::RenderResource* m_dummy;  // "cmn_stream_dummy", requested by the constructor
};
}  // namespace ui

#endif
