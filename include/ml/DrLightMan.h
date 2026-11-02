#ifndef ML_DRLIGHTMAN_H
#define ML_DRLIGHTMAN_H

#include "classes/ml/DrLightObj.h"
#include "mm/Col3.h"
#include "mm/Vec3.h"

namespace ml {
class DrMan;
class DrLightObjAmb;
class DrLightObjDir;
class DrLightObjPnt;
class DrLightObjSpt;
class DrShdLgtMan;

// DrMan's light manager (DrMan::m_lightMan). Only what DrResMdoLight calls is declared.
class DrLightMan {
public:
    DrLightObjPnt* createInstantPntLight();
    DrLightObjSpt* createInstantSptLight();
    // 1.0.0 has both out of line (3.0.1 inlines them into releaseFastLight and drops the copies)
    void releaseAmbLight(DrLightObjAmb* light);
    void releaseDirLight(DrLightObjDir* light);
    void releasePntLight(DrLightObjPnt* light);
    void releaseSptLight(DrLightObjSpt* light);
    void releaseInstantPntLight(DrLightObjPnt* light);
    void releaseInstantSptLight(DrLightObjSpt* light);
    // ScnObjLightDrSys's constructor calls it when the pool holds no environment light yet
    void releaseFastLight();
    ~DrLightMan();
    void releaseAll();
    void releaseAllAmbLight();
    void releaseAllDirLight();
    float getSkyLuminance() const;
    // around the frame's light stocking; they bracket DrShdLgtMan's own stockBegin/stockEnd
    void stockBegin();
    // the frame's update: the ambient and directional lights, then the point and spot lights stocked for the frame
    // (by DrMan::s_nDblIdx) join the lists
    void update();
    void updateAmb();
    void updateDir();
    void stockEnd();
    void updateAfterPnt();
    void updateAfterSpt();

    // a head/tail list of lights, linked through DrLightObj::m_next (the name is not the original's)
    struct LightList {
        // deletes every light through its table, walking m_next, and empties the list (inline: no symbol; the
        // name is not the original's)
        void deleteAll() {
            DrLightObj* obj = m_head;
            while (obj != nullptr) {
                DrLightObj* next = obj->m_next;
                delete obj;
                obj = next;
            }
            m_head = nullptr;
            m_tail = nullptr;
        }
        // appends obj at the tail (inline: no symbol; the name is not the original's)
        void append(DrLightObj* obj) {
            if (m_tail != nullptr) {
                m_tail->m_next = obj;
                obj->m_prev = m_tail;
                m_tail = obj;
            } else {
                m_head = m_tail = obj;
                obj->m_prev = nullptr;
            }
            obj->m_next = nullptr;
        }
        DrLightObj* m_head;
        DrLightObj* m_tail;
    };

    // releaseAllAmbLight/releaseAllDirLight empty them; by DrLightObj::TYPE_* (the names are not the original's)
    LightList m_list[4];  // 0x0
    LightList m_stockList[4][2];  // 0x40, createAmbLight appends to [TYPE_AMB][stock index]
    unsigned char pad_c0[0x20];
    DrMan* m_drMan;  // 0xE0, the renderer (stockBegin reaches DrShdLgtMan through its m_shdMan; the name is not the original's)
    DrShdLgtMan* m_shdLgtMan;  // 0xE8, the constructor caches drMan->m_shdMan->m_lgtMan (the name is not the original's)
    DrLightObj* m_ambLight;  // 0xF0, releaseAllAmbLight clears it (the name is not the original's)
    DrLightObj* m_dirLight;  // 0xF8, releaseAllDirLight clears it (the name is not the original's)
    int m_ambNum;  // 0x100, createAmbLight counts up, releaseAllAmbLight clears (the name is not the original's)
    int m_dirNum;  // 0x104, releaseAllDirLight clears it (the name is not the original's)
    // instant lights in use: releaseInstant*Light count them down, never below 0 (the names are not the original's)
    int m_instantPntNum;  // 0x108
    int m_instantSptNum;  // 0x10C
    unsigned char pad_110[0x10];
    float m_lumColor[3];  // 0x120, getSkyLuminance weighs it with m_ambColor (the name is not the original's)
    // 0x12C: DrCalcViewWork::unistatic_lightAmb's colour; DrEnvironmentObjLgt::updatePosLgt copies its m_ambColor
    // here (the name is not the original's)
    mm::Col3 m_ambColor;
    unsigned char pad_138[0x30];
    // stockBegin clears both (the names are not the original's)
    int m_stockCount;  // 0x168
    // 0x16C: the stocked directional lights' colours; DrCalcViewWork::unistatic_lightCol hands the first
    // m_stockCount (at most 2) to the shader (the name is not the original's)
    mm::Col3 m_stockColor[2];
    unsigned char pad_184[0xC];
    // 0x190: the stocked directional lights' directions; DrCalcViewWork::unistatic_lightDir hands them, negated
    // and turned into view space, to the shader (the name is not the original's)
    mm::Vec3 m_stockDir[2];
    unsigned char pad_1B0[0x8];
    short m_stockState;  // 0x1B8
};
}  // namespace ml

#endif
