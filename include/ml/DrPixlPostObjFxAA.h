#ifndef ML_DRPIXLPOSTOBJFXAA_H
#define ML_DRPIXLPOSTOBJFXAA_H

#include "ml/DrPixlPostObj.h"
#include "ml/DrPixlRenderTarget.h"
#include "classes/ml/DrMan.h"
#include "mtl/MemManager.h"

namespace ml {
// DrPixlPostMan::m_fxaa (0x28 bytes, no table); the constructor is inline in DrPixlPostMan's. Only what
// DrPixlPostMan uses is declared; the field names are not the original's.
class DrPixlPostObjFxAA : public DrPixlPostObj {
public:
    DrPixlPostObjFxAA(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
        m_target = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(drMan);
        m_width = m_drMan->m_curViewInfo->m_width;
        m_height = m_drMan->m_curViewInfo->m_height;
    }
    ~DrPixlPostObjFxAA() {
        if (m_target != nullptr) {
            delete m_target;
            m_target = nullptr;
        }
    }
    void calcScale();

    DrPixlRenderTarget* m_target;  // 0x18, made by the constructor
    // 0x20: the view size; the constructor and DrPixlPostMan::resetColorBuff set it from DrMan::m_curViewInfo
    float m_width;
    float m_height;  // 0x24
};
}  // namespace ml

#endif
