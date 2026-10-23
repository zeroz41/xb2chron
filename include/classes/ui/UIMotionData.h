#ifndef CLASSES_UI_UIMOTIONDATA_H
#define CLASSES_UI_UIMOTIONDATA_H

namespace mm { namespace mtl { class IAllocator; } }

namespace ui {
// table 0x7100B74D70
class UIMotionData {
public:
    UIMotionData(mm::mtl::IAllocator* allocator);
    virtual ~UIMotionData();  // slot 0
    void deserialize(const void* data, unsigned int size);  // a motion file's (UIMotionLibrary::update's)
    unsigned char pad_08[0x58];  // 0x60 bytes: UIMotionLibrary::update allocates them so
};
}  // namespace ui

#endif
