#ifndef ML_DRLIGHTMAN_H
#define ML_DRLIGHTMAN_H

namespace ml {
class DrMan;
class DrLightObjPnt;
class DrLightObjSpt;

// DrMan's light manager (DrMan::m_lightMan). Only what DrResMdoLight calls is declared.
class DrLightMan {
public:
    DrLightObjPnt* createInstantPntLight();
    void releasePntLight(DrLightObjPnt* light);
    void releaseSptLight(DrLightObjSpt* light);
    void releaseInstantPntLight(DrLightObjPnt* light);
    void releaseInstantSptLight(DrLightObjSpt* light);
    // ScnObjLightDrSys's constructor calls it when the pool holds no environment light yet
    void releaseFastLight();
    ~DrLightMan();
    void releaseAll();
    // around the frame's light stocking; they bracket DrShdLgtMan's own stockBegin/stockEnd
    void stockBegin();
    void stockEnd();
    void updateAfterPnt();
    void updateAfterSpt();

    unsigned char pad_0[0xE0];
    DrMan* m_drMan;  // 0xE0, the renderer (stockBegin reaches DrShdLgtMan through its m_shdMan; the name is not the original's)
    unsigned char pad_e8[0x20];
    // instant lights in use: releaseInstant*Light count them down, never below 0 (the names are not the original's)
    int m_instantPntNum;  // 0x108
    int m_instantSptNum;  // 0x10C
    unsigned char pad_110[0x1C];
    float m_ambColor[3];  // 0x12C: DrCalcViewWork::unistatic_lightAmb's colour (the name is not the original's)
    unsigned char pad_138[0x30];
    // stockBegin clears both (the names are not the original's)
    int m_stockCount;  // 0x168
    unsigned char pad_16c[0x4C];
    short m_stockState;  // 0x1B8
};
}  // namespace ml

#endif
