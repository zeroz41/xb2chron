#ifndef CLASSES_EVENT_LIGHTEVT_H
#define CLASSES_EVENT_LIGHTEVT_H

#include "mm/mtl/FixStr.h"
#include "classes/ml/ScnObjLight.h"
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3D1C0
class LightEvt {
public:
    // 1.0.0's LightEvt() (0x71000E29A8; 3.0.1 inlines it: playOffScrLight)
    LightEvt() : m_lgt(nullptr), m_name(), m_lgtParam(0) {}
    virtual ~LightEvt();  // slot 0
    // out of line (LightManager::render calls it): the light's debug panel at x, y
    void render(int x, int y);
    // 0x71000F75E4 (1.0.0's symbol names it): clear(), keeps the name, then the light the scene creates from the resource
    void play(void* res, const char* name, unsigned int param);
    // 1.0.0's clear (0x71000E2A18; 3.0.1 inlines it, defined inline in CharaObj.cpp)
    void clear();
    // 1.0.0's isPlaying (0x71000E2CD8; 3.0.1 inlines it)
    bool isPlaying() const { return m_lgt != nullptr; }
    // 1.0.0's setPos (0x71000E2CE8; 3.0.1 inlines it): the light's offset position
    void setPos(const mm::Vec3& pos) {
        if (m_lgt) {
            m_lgt->setOffsetPos(pos);
        }
    }
    // play (0x71000F75E4) releases the previous light to the scene, keeps the name, then the light the scene creates
    // and the int it was created with (the names are not the original's)
    // a light: setPos calls its setOffsetPos (ScnObjLight's slot 16)
    ml::ScnObjLight* m_lgt;  // 0x8
    mm::mtl::FixStr<128> m_name;  // 0x10
    unsigned int m_lgtParam;  // 0x94
};
}  // namespace event

#endif
