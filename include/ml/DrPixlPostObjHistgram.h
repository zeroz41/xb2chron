#ifndef ML_DRPIXLPOSTOBJHISTGRAM_H
#define ML_DRPIXLPOSTOBJHISTGRAM_H

#include "ml/DrPixlPostObj.h"
#include "ml/DrResQueryObj.h"
#include "mtl/MemManager.h"

namespace ml {
// DrPixlPostMan::m_histgram (0xC0 bytes, its constructor inline in DrPixlPostMan's). Only what DrPixlPostMan uses
// is declared.
class DrPixlPostObjHistgram : public DrPixlPostObj {
public:
    DrPixlPostObjHistgram(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
        : DrPixlPostObj(drMan, pixlMan, postMan), m_query(nullptr), m_counter(0), m_mode(1), m_lumMin(100000.0f), m_lumMax(0.0f),
          m_interval(11), m_ready(false) {
        m_query = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrResUseQueryObj();
        resetMaxLuminance(32.0f);
    }
    ~DrPixlPostObjHistgram() {
        if (m_query != nullptr) {
            delete m_query;
            m_query = nullptr;
        }
    }
    void update();
    void render();
    void resetMaxLuminance(float);

    DrResUseQueryObj* m_query;  // 0x18, made by the constructor (name inferred)
    // 0x20: resetMaxLuminance's luminance thresholds: ten steps up to the maximum (linear in mode 0, logarithmic
    // from 1/256 in mode 1), then the maximum and 100000 (the name is not the original's)
    float m_lumTbl[11];
    unsigned int m_count[22];  // 0x4C, resetMaxLuminance clears it (the name is not the original's)
    // 0xA4..0xB8: only the constructor's values are known; the names are inferred, not the original's
    int m_counter;  // 0xA4, resetMaxLuminance reads and writes it
    int m_mode;  // 0xA8, resetMaxLuminance switches on 0 and 1; the constructor sets 1
    float m_lumMin;  // 0xAC, 100000 at first
    float m_lumMax;  // 0xB0
    int m_interval;  // 0xB4, 11 at first
    bool m_ready;  // 0xB8
    unsigned char pad_B9[0x7];
};
}  // namespace ml

#endif
