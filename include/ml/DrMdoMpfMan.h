#ifndef ML_DRMDOMPFMAN_H
#define ML_DRMDOMPFMAN_H

#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibTriUniformBlock.h"
#include "ml/DrMdoCtlMpfWindCalc.h"

namespace ml { class DrMan; }
namespace ml { struct _MPFWorkAutoInf; }

namespace ml {
// Owns the frame's MPF work memory (no vtable: its constructor stores no table). Only the fields this unit's
// matched functions touch are spelled out; field names are not the original's.
class DrMdoMpfMan {
public:
    explicit DrMdoMpfMan(DrMan* drMan);
    ~DrMdoMpfMan();

    void begin();
    void update();
    void updateUniformWork();
    void addMpfObj();
    bool delMpfObj();
    void freeMemWork(_MPFWorkAutoInf* inf);

    // Hands out the next `size` bytes of the frame work buffer (inlined into DrMdoCtlMpfWork's *Set functions;
    // the name is not the original's).
    char* getFrameWork(int size) {
        char* work = m_pFrameWork + m_frameWorkUsed;
        m_frameWorkUsed += size;
        return work;
    }

    DrMan* m_pDrMan;  // 0x0
    int m_mpfObjNum;  // 0x8, counted by addMpfObj/delMpfObj
    unsigned char pad_C[0xC];
    // 0x18, the constructor sets it up (0x1800 bytes); mpfshd_stm_wind binds it (the name is not the original's)
    grlib::CGLibTriUniformBlock m_windBlock;
    // 0x60, the constructor sets it up (0x10 bytes); updateUniformWork writes half of DrLightMan::m_ambColor into it
    // (the name is not the original's)
    grlib::CGLibDblUniformBlock m_ambBlock;
    grlib::CGLibDblUniformBlock pad_98;  // 0x98: only constructed, released and destroyed here
    int m_listCount;  // 0xD0, cleared by begin()
    unsigned char pad_D4[0x4];
    // 0xD8: free work blocks (_MPFWorkAutoInf::m_pNext/m_pPrev), DrMdoCtlMpfAuto::getMemWork takes from it
    _MPFWorkAutoInf* m_pFreeHead;
    _MPFWorkAutoInf* m_pFreeTail;  // 0xE0
    unsigned char pad_E8[0x8];
    _MPFWorkAutoInf* m_pFreeLargest;  // 0xF0: setHeMemWork's largest too-small block when none fits
    unsigned char pad_F8[0x8];
    DrMdoCtlMpfWindCalc m_windCalc[64];  // 0x100: the constructor inits each, update runs calcUpdate on each
    unsigned char pad_3D00[0x10];
    char* m_pFrameWork;  // 0x3D10
    unsigned char pad_3D18[0x8];
    int m_frameWorkUsed;  // 0x3D20, cleared by begin()
    float m_windScale;  // 0x3D24, 1.0f from begin(); update scales the wind by it
    void* m_pWorkBuff;  // 0x3D28: the constructor's allocation (0x2E5A20 bytes), freed by the destructor
    // 0x3D30: update sets bit 0 each call and runs (clearing it) only while bit 1 is set (the name is not the
    // original's)
    unsigned int m_updateFlags;
    unsigned char pad_3D34[0xC];  // to 0x3D40, the size DrMdlMan::addMpfObj allocates
};
}  // namespace ml

#endif
