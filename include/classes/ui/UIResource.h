#ifndef CLASSES_UI_UIRESOURCE_H
#define CLASSES_UI_UIRESOURCE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"

namespace fw { class CommonResource; }
namespace grlib { class CGLibTextureBuffer; }
namespace ml { class ScnRenderDrViewCtrl; }
namespace mm { namespace mtl { class IAllocator; } }
namespace ui { class UIBuildInfo; }

namespace ui {
// table 0x7100B757F8; counted: its constructor zeroes the count at 0x8, UIFontManager releases it as
// reference_object.h does (`m_RefCount > 0`, then slot 1)
class UIResource : public ::mm::mtl::ReferenceObject {
public:
    // a resource load requested (the names are the symbols' Vector<ui::UIResource::ResourceInfo>; the field names
    // are not the original's)
    struct ResourceInfo {
        fw::CommonResource* m_resource;  // referenced; releaseResourceList releases it
        bool m_isRemovable;  // set from the build entry: fn_71006943A0 drops the entry once it loaded empty
    };
    // a render view load made for a layout of type 4 (the field names are not the original's)
    struct RenderViewInfo {
        ml::ScnRenderDrViewCtrl* m_view;  // created through ScnRenderDrSysParmAcc::createAddRenderView
        unsigned int m_hash;  // mm::mtl::hashStrCrc of the entry's name (searchRednerView compares it)
    };
    // what searchCapture hands out: a capture texture and its size (the names are not the original's)
    struct Capture {
        grlib::CGLibTextureBuffer* m_texture;
        int m_width;
        int m_height;
        unsigned short m_flags;
    };
    // a capture texture made for an image layout (the field names are not the original's)
    struct CaptureInfo {
        grlib::CGLibTextureBuffer* m_texture;  // new'd in load, deleted by releaseCaptureList
        Capture m_capture;
        unsigned int m_hash;  // mm::mtl::hashStrCrc of the entry's name (searchCapture compares it)
    };

    UIResource(const char* name);
    virtual ~UIResource();  // slot 0
    void releaseRenderViewList();
    void releaseResourceList();
    void releaseCaptureList();
    void load(const UIBuildInfo* info, mm::mtl::IAllocator* allocator);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it walks m_resourceList (this
    // at 0x30 handed to Vector::erase), defined between load and isValid. What it does: when the list has room and
    // entries, erases each entry whose m_isRemovable is set and whose resource is valid() with getAssetSize() 0.
    // Called by UIObjFactory::update.
    void fn_71006943A0();
    bool isValid() const;
    bool isLoading() const;
    fw::CommonResource* search(const char* name) const;  // the loaded resource of that file name, or null
    ml::ScnRenderDrViewCtrl* searchRednerView(const char* name) const;  // (sic) the view of that name, or null
    Capture* searchCapture(const char* name);  // the capture of that name, or null

    mm::mtl::FixStr<32> m_name;  // the constructor's (UIFontManager::update reads the BDAT table of that name)
    // the names are not the original's (1.0.0's releaseResourceList, releaseRenderViewList, releaseCaptureList)
    mm::mtl::Vector<ResourceInfo> m_resourceList;
    mm::mtl::Vector<RenderViewInfo> m_renderViewList;
    mm::mtl::Vector<CaptureInfo> m_captureList;
};
}  // namespace ui

#endif
