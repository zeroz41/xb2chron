#ifndef CLASSES_ML_DRRESMDOINSTPARTSANM_H
#define CLASSES_ML_DRRESMDOINSTPARTSANM_H

#include "classes/ml/DrResMdoInstPartsObj.h"

namespace ml {
// table 0x7100B7D8A8
class DrResMdoInstPartsAnm {
public:
    virtual ~DrResMdoInstPartsAnm();  // slot 0
    virtual void setPosFrame(float frame) { m_posFrame = frame; }  // slot 2
    virtual float getPosFrame() const { return m_posFrame; }  // slot 3
    virtual float getPosMaxFrame() const {
        if (m_posAnm) {
            return m_posAnm->frameMax * m_frameScale;
        }
        return 0.0f;
    }  // slot 4
    virtual float getPosStartFrame() const {
        if (m_posAnm && m_info->startFrame) {
            return m_info->startFrame * (1.0f / 255.0f) * m_posAnm->frameMax;
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

    // The position animation the part reads (0x30); type and field names are not the original's.
    struct PosAnm {
        unsigned char pad_0[0x152];
        unsigned short frameMax;  // 0x152: get*PosMaxFrame scales it
    };
    // One switch entry (0x24 bytes; getSwitchIndex reads its byte 2); names are not the original's.
    struct Switch {
        unsigned char pad_0[0x2];
        unsigned char index;  // 0x2
        unsigned char pad_3[0x21];
    };

    // Field names are not the original's: each follows the getter/setter that reads or writes it.
    unsigned int m_stockFlags;          // 0x8: bit n = m_nodeFrameStock[n] set (setNodeFrame)
    unsigned char pad_c[0xC];
    const DrResMdoInstPartsObj::Info* m_info;  // 0x18
    unsigned char pad_20[0x10];
    const PosAnm* m_posAnm;             // 0x30
    unsigned char pad_38[0x8];
    float m_posFrame;                   // 0x40
    float m_nodeFrame;                  // 0x44
    float m_oldNodeFrame;               // 0x48 (getCalcOldNodeFrame)
    float m_nodeFrameStock[2];          // 0x4C: per DrMan double-buffer index
    float m_frameScale;                 // 0x54 (get*MaxFrame)
    float m_nodeFrameRate;              // 0x58 (getCalc*NodeFrame)
    unsigned short m_nodeFrameBase;     // 0x5C (getCalc*NodeFrame)
    unsigned short m_nodeFrameMax;      // 0x5E (getNode*Frame)
    unsigned char pad_60[0x8];
    const Switch* m_switches;           // 0x68
    unsigned char m_switchID;           // 0x70
    unsigned char m_switchMax;          // 0x71
};
}  // namespace ml

#endif
