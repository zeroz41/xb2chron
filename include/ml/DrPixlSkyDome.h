#ifndef ML_DRPIXLSKYDOME_H
#define ML_DRPIXLSKYDOME_H

#include "ml/DrResQueryObj.h"
#include "mm/Vec3.h"
#include "mtl/MemManager.h"

namespace ml {
// DrPixlPostMan::m_skyDome (0x50 bytes, its constructor inline in DrPixlPostMan's). Only what DrPixlMan uses is
// declared; the field names are not the original's.
class DrPixlSkyDome {
public:
    DrPixlSkyDome(DrMan* drMan)
        : m_drMan(drMan), m_query(nullptr), m_visible(0.0f), m_holdFrames(0), m_param0(1.0f, 1.0f, 1.0f),
          m_param1(0.5f, 0.5f, 0.5f), m_param2(0.0f, 0.0f, 0.0f) {
        m_query = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrResUseQueryObj();
    }
    ~DrPixlSkyDome() {
        if (m_query != nullptr) {
            delete m_query;
            m_query = nullptr;
        }
    }
    void baseRender();
    void godRayRender();
    void updateUniform();

    DrMan* m_drMan;  // 0x0
    DrResUseQueryObj* m_query;  // 0x8, DrPixlPostMan::update updates it and fades m_visible to whether it passed
    // 0x10: eases to 1 while m_query passes (by half a frame) and to 0 otherwise (by 0.2); held at 1 for m_holdFrames
    float m_visible;
    int m_holdFrames;  // 0x14, set to 3 while DrCalcViewWork::m_gpuCheckAllVisible
    unsigned char pad_18[0x8];
    // 0x20..0x40: the constructor sets them to 1, 0.5 and 0 (names inferred)
    mm::Vec3 m_param0;
    mm::Vec3 m_param1;  // 0x30
    mm::Vec3 m_param2;  // 0x40
};
}  // namespace ml

#endif
