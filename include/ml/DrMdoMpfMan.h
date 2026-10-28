#ifndef ML_DRMDOMPFMAN_H
#define ML_DRMDOMPFMAN_H

namespace ml { class DrMan; }

namespace ml {
// Owns the frame's MPF work memory (no vtable: its constructor stores no table). Only the fields this unit's
// matched functions touch are spelled out; field names are not the original's.
class DrMdoMpfMan {
public:
    explicit DrMdoMpfMan(DrMan* drMan);
    ~DrMdoMpfMan();

    void begin();
    void update();
    void addMpfObj();
    bool delMpfObj();

    // Hands out the next `size` bytes of the frame work buffer (inlined into DrMdoCtlMpfWork's *Set functions;
    // the name is not the original's).
    char* getFrameWork(int size) {
        char* work = m_pFrameWork + m_frameWorkUsed;
        m_frameWorkUsed += size;
        return work;
    }

    DrMan* m_pDrMan;  // 0x0
    int m_mpfObjNum;  // 0x8, counted by addMpfObj/delMpfObj
    unsigned char pad_C[0xC4];
    int m_listCount;  // 0xD0, cleared by begin()
    unsigned char pad_D4[0x3C3C];
    char* m_pFrameWork;  // 0x3D10
    unsigned char pad_3D18[0x8];
    int m_frameWorkUsed;  // 0x3D20, cleared by begin()
    float m_windScale;  // 0x3D24, 1.0f from begin(); update scales the wind by it
    unsigned char pad_3D28[0x10];
};
}  // namespace ml

#endif
