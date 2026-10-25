#ifndef CLASSES_ML_DRRESMDOINSTPARTSOBJ_H
#define CLASSES_ML_DRRESMDOINSTPARTSOBJ_H

#include "mm/Mat44.h"

namespace ml {
// table 0x7100B7D7F8
class DrResMdoInstPartsObj {
public:
    virtual ~DrResMdoInstPartsObj() {}  // slot 0
    virtual void setPosFrame(float) {}  // slot 2
    virtual float getPosFrame() const { return 0.0f; }  // slot 3
    virtual float getPosMaxFrame() const { return 0.0f; }  // slot 4
    virtual float getPosStartFrame() const { return 0.0f; }  // slot 5
    virtual void setNodeFrame(float) {}  // slot 6
    virtual float getNodeFrame() const { return 0.0f; }  // slot 7
    virtual float getCalcNodeFrame() const { return 0.0f; }  // slot 8
    virtual float getCalcOldNodeFrame() const { return 0.0f; }  // slot 9
    virtual float getNodeMaxFrame() const { return 0.0f; }  // slot 10
    virtual float getNodeStartFrame() const { return 0.0f; }  // slot 11
    virtual unsigned char getSwitchID() const { return 0; }  // slot 12
    virtual void setSwitchID(unsigned char) {}  // slot 13
    virtual unsigned char getSwitchMax() const { return 0; }  // slot 14
    virtual unsigned char getSwitchIndex(unsigned int) const { return 1; }  // slot 15
    virtual void update() {}  // slot 16
    virtual void getMatrix(mm::Mat44&) const;  // slot 17
    virtual void getAnmMatrix(mm::Mat44& m) const { getMatrix(m); }  // slot 18
    virtual void setMatrix(mm::Mat44 const&) {}  // slot 19

    // The record a part's object reads (0x18); type and field names are not the original's.
    struct Info {
        unsigned int nameOfs;      // 0x0: name string offset in the object's name block (ScnObjAccPartsPos::getName)
        unsigned char pad_4[0x4];
        unsigned short id;         // 0x8 (ScnObjAccPartsPos::getID)
        unsigned short flags;      // 0xA: 0x20 = has a matrix (getMatrix), 0x80 = has switches (setSwitchID)
        unsigned char startFrame;  // 0xC: start frame in 1/255 of the max frame (get*StartFrame)
    };

    unsigned int m_flags;      // 0x8: bit 2 loop, bit 3 collision off, bit 4 collision skip data (ScnObjAccPartsPos)
    unsigned char pad_C[0x4];
    const char* m_names;       // 0x10: the name block Info::nameOfs indexes (ScnObjAccPartsPos::getName)
    const Info* m_info;        // 0x18; the name is not the original's
    const mm::Mat44* m_matrix; // 0x20: getMatrix copies it; the name is not the original's
    float m_alpha;             // 0x28: ScnObjAccPartsPos::setAlpha (1.0.0 also has getAlpha); the name is not the original's
};
}  // namespace ml

#endif
