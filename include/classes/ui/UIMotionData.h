#ifndef CLASSES_UI_UIMOTIONDATA_H
#define CLASSES_UI_UIMOTIONDATA_H

namespace mm { namespace mtl { class IAllocator; } }

namespace ui {
// table 0x7100B74D70
class UIMotionData {
public:
    // a motion's values at a frame or over a span (UICtrlMethodMotion::execute; the field names are not the
    // original's)
    struct MotionParam {
        unsigned int m_flags;  // bit 2: m_scaleX given, bit 3: m_scaleY given, bit 5: m_alpha given
        float m_posX;
        float m_posY;
        float m_scaleX;
        float m_scaleY;
        float m_rot;
        float m_alpha;
    };

    UIMotionData(mm::mtl::IAllocator* allocator);
    virtual ~UIMotionData();  // slot 0
    void deserialize(const void* data, unsigned int size);  // a motion file's (UIMotionLibrary::update's)
    int searchMotion(const char* name) const;  // the index of a motion by its name (UICtrlMethodMotion::setup)
    float getMotionLength(unsigned int index) const;  // a motion's length in seconds (GfMenuObjUtil::getCtrlMotionTime)
    // the motion's values at its first frame; false for an index out of range
    bool getMotionParamDefault(unsigned int index, MotionParam& param) const;
    // what the motion's values change by from time to time + step
    bool getMotionParamDelta(unsigned int index, float time, float step, MotionParam& param) const;
    unsigned char pad_08[0x58];  // 0x60 bytes: UIMotionLibrary::update allocates them so
};
}  // namespace ui

#endif
