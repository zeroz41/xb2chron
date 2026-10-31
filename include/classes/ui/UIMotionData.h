#ifndef CLASSES_UI_UIMOTIONDATA_H
#define CLASSES_UI_UIMOTIONDATA_H

#include "mm/mtl/Vector.h"

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

    // one value a frame sets (8 bytes, read from the motion file as they are; the field names are not the original's)
    struct Parameter {
        unsigned short m_type;   // 1: the frame's kind (getMotionParamFrame's third argument), 2..7: a MotionParam field
        unsigned short m_flags;  // 0 or bit 1: m_value as it is; bit 0: m_value indexes m_names
        union Value {
            float f;
            unsigned int u;
            int i;
        };
        Value m_value;
    };
    // a motion: its frames' parameters and its name's index in m_names (the field names are not the original's)
    struct MotionData {
        mm::mtl::Vector<mm::mtl::Vector<Parameter> > m_frames;  // one Parameter list a frame (30 a second)
        unsigned int m_nameIndex;
        MotionData() : m_nameIndex(0) {}
    };

    UIMotionData(mm::mtl::IAllocator* allocator);
    virtual ~UIMotionData();  // slot 0
    void clear();
    void deserialize(const void* data, unsigned int size);  // a motion file's (UIMotionLibrary::update's)
    int searchMotion(const char* name) const;  // the index of a motion by its name (UICtrlMethodMotion::setup)
    float getMotionLength(unsigned int index) const;  // a motion's length in seconds (GfMenuObjUtil::getCtrlMotionTime)
    // the motion's values at its first frame; false for an index out of range
    bool getMotionParamDefault(unsigned int index, MotionParam& param) const;
    // a frame's values and kind; false for an index or frame out of range
    bool getMotionParamFrame(unsigned int index, unsigned int frame, unsigned int& kind, MotionParam& param) const;
    // what the motion's values change by from time to time + step
    bool getMotionParamDelta(unsigned int index, float time, float step, MotionParam& param) const;
    // 0x60 bytes: UIMotionLibrary::update allocates them so (the field names are not the original's)
    mm::mtl::Vector<MotionData> m_motions;  // 0x08
    mm::mtl::Vector<const char*> m_names;   // 0x30, into the file's name block
    mm::mtl::IAllocator* m_allocator;       // 0x58, the constructor's; the motions' lists come from it
};
}  // namespace ui

#endif
