#ifndef CLASSES_ML_DRRESMDOINSTPARTSANM_H
#define CLASSES_ML_DRRESMDOINSTPARTSANM_H

#include "classes/ml/DrResMdoInstPartsObj.h"
#include "ml/DrResMdoPosInstAnm.h"

namespace ml {
// table 0x7100B7D8A8
class DrResMdoInstPartsAnm {
public:
    virtual ~DrResMdoInstPartsAnm();  // slot 0
    virtual void setPosFrame(float frame) { m_posFrame = frame; }  // slot 2
    virtual float getPosFrame() const { return m_posFrame; }  // slot 3
    virtual float getPosMaxFrame() const {
        if (m_posAnm) {
            return m_posAnm->m_frameMax * m_frameScale;
        }
        return 0.0f;
    }  // slot 4
    virtual float getPosStartFrame() const {
        if (m_posAnm && m_info->startFrame) {
            return m_info->startFrame * (1.0f / 255.0f) * m_posAnm->m_frameMax;
        }
        return 0.0f;
    }  // slot 5
    virtual void setNodeFrame(float);  // slot 6
    virtual float getNodeFrame() const;  // slot 7
    virtual float getCalcNodeFrame() const { return m_nodeFrameBase + m_nodeFrame * m_nodeFrameRate; }  // slot 8
    virtual float getCalcOldNodeFrame() const { return m_nodeFrameBase + m_oldNodeFrame * m_nodeFrameRate; }  // slot 9
    virtual float getNodeMaxFrame() const { return m_nodeFrameMax * m_frameScale; }  // slot 10
    virtual float getNodeStartFrame() const {
        if (m_nodeFrameMax && m_info->startFrame) {
            float rate = m_info->startFrame * (1.0f / 255.0f);
            return m_nodeFrameMax * rate;
        }
        return 0.0f;
    }  // slot 11
    virtual unsigned char getSwitchID() const { return m_switchID; }  // slot 12
    virtual void setSwitchID(unsigned char);  // slot 13
    virtual unsigned char getSwitchMax() const { return m_switchMax; }  // slot 14
    virtual unsigned char getSwitchIndex(unsigned int) const;  // slot 15
    virtual void update();  // slot 16
    virtual void getMatrix(mm::Mat44&) const;  // slot 17
    virtual void getAnmMatrix(mm::Mat44&) const;  // slot 18
    virtual void setMatrix(mm::Mat44 const&);  // slot 19

    void updateSwitch();

    // One visibility key (8 bytes) and the key header update reads; names are not the original's.
    struct VisKey {
        float value;           // 0x0: visible when above 0.001
        unsigned short frame;  // 0x4
        unsigned char pad_6[0x2];
    };
    struct VisAnm {
        unsigned int keyOffset;   // 0x0: from m_data
        unsigned char pad_4[0x2];
        unsigned short keyNum;    // 0x6
        unsigned short startFrame;  // 0x8
        unsigned short endFrame;    // 0xA
    };
    // One switch entry (0x24 bytes; getSwitchIndex reads its byte 2); names are not the original's.
    // updateSwitch reads flags (0x1 = sets the node frame range, 0x2 = sets m_stockFlags bit 2) and the range.
    struct Switch {
        unsigned short flags;  // 0x0
        unsigned char index;   // 0x2
        unsigned char pad_3[0x1];
        // 0x4: the node frame range (bit-fields: updateSwitch reads both with one 32-bit load)
        unsigned int startFrame : 16;
        unsigned int endFrame : 16;
        unsigned char pad_8[0x1C];
    };

    // Field names are not the original's: each follows the getter/setter that reads or writes it.
    unsigned int m_stockFlags;          // 0x8: bit n = m_nodeFrameStock[n] set (setNodeFrame)
    unsigned char pad_c[0x4];
    const unsigned char* m_data;        // 0x10: update finds the visibility keys at m_data + m_visAnm->keyOffset
    const DrResMdoInstPartsObj::Info* m_info;  // 0x18
    const mm::Mat44* m_matrix;         // 0x20: getAnmMatrix copies it when the info has a matrix (flag 0x20)
    unsigned char pad_28[0x8];
    DrResMdoPosInstAnm* m_posAnm;       // 0x30: getAnmMatrix calls its getAnmMatrix
    unsigned char pad_38[0x8];
    float m_posFrame;                   // 0x40
    float m_nodeFrame;                  // 0x44
    float m_oldNodeFrame;               // 0x48 (getCalcOldNodeFrame)
    float m_nodeFrameStock[2];          // 0x4C: per DrMan double-buffer index
    float m_frameScale;                 // 0x54 (get*MaxFrame)
    float m_nodeFrameRate;              // 0x58 (getCalc*NodeFrame)
    unsigned short m_nodeFrameBase;     // 0x5C (getCalc*NodeFrame)
    unsigned short m_nodeFrameMax;      // 0x5E (getNode*Frame)
    const VisAnm* m_visAnm;             // 0x60: update sets m_stockFlags bit 3 from it (0 = none)
    const Switch* m_switches;           // 0x68
    unsigned char m_switchID;           // 0x70
    unsigned char m_switchMax;          // 0x71
};
}  // namespace ml

#endif
